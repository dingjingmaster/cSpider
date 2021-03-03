package daemon

import (
	"fmt"
	"os"
	"os/exec"
	"spider/config"
	"spider/logs"
	"strconv"
	"syscall"
	"time"
)

var runIndex = 0
const EnvName = config.FullName

type Daemon struct {
	Stop 				bool 	// 是否退出
	MaxError 			int 	// 连续重启最大次数，超过此数字则退出守护进程
	MinExitTime			int64 	// 子进程正常退出的最小时间(秒)，小于此时间则认为是正常退出
}

/**
 * 把本身程序转化为后台运行(启动一个子进程，然后自己退出)
 */
func Background (isExit bool) (*exec.Cmd, error) {
	// 判断是子进程还是父进程
	runIndex++
	_, err := strconv.Atoi(os.Getenv(EnvName))
	if nil != err {
		logs.Log.Informational("%v", err)
	}

	// 设置子进程环境变量，启动次数
	env := os.Environ()
	env = append (env, fmt.Sprintf("%d", runIndex))

	// 启动子进程
	cmd, err := startProc (os.Args, env)
	if nil != err {
		logs.Log.Error("sub process start error:%v", err)
		return nil, err
	} else {
		logs.Log.Informational("sub process start ok!")
	}

	if isExit {
		os.Exit(0)
	}

	return cmd, nil
}

func NewDaemon () *Daemon {
	return &Daemon{
		MaxError: 		3,
		MinExitTime: 	10,
	}
}

/**
 * 启动后台守护进程
 */
func (d* Daemon) Run () {
	Background(true)		// 启动一个守护进程之后退出

	errNum := 0
	// 守护进程启动一个子进程并循环监视
	for !d.Stop {
		// daemon 描述信息
		if errNum > d.MaxError {
			logs.Log.Emergency("pid:%d, errNum:%d/%d sub process fail too many times", os.Getpid(), errNum, d.MaxError)
			os.Exit(1)
		}

		t := time.Now().Unix()	// 启动时间戳
		cmd, err := Background(false)
		if nil != err {
			logs.Log.Alert("sub process start failed! %s", err)
			errNum++
			continue
		}

		// 子进程
		if nil == cmd {
			logs.Log.Informational("sub process pid:%d starting...", os.Getpid())
			break
		}

		// 父进程
		err = cmd.Wait()
		dat := time.Now().Unix() - t

		if dat < d.MinExitTime {
			errNum++
		} else {
			errNum = 0
		}

		logs.Log.Informational("sub process pid:%d runs %d second, error:%v", cmd.ProcessState.Pid(), dat, err)
	}
}

func startProc (args, env []string) (*exec.Cmd, error) {
	cmd := &exec.Cmd {
		Path:			args[0],
		Args:			args,
		Env: 			env,
		SysProcAttr: 	&syscall.SysProcAttr {Setsid: true},
	}

	err := cmd.Start()
	if nil != err {
		return nil, err
	}

	return cmd, nil
}