package main

import (
	"flag"
	"fmt"
	"os"
	"spider/app"
	"spider/config"
	"spider/daemon"
	"spider/exec"
	"spider/runtime/cache"
	"spider/runtime/status"
	_ "spider/spiders" // 此为公开维护的spider规则库
	"strconv"
	"strings"
	"syscall"
)

var (
	port               	*int
	runType 		    *string
	master             	*string
	keyinsflag         	*string
	limitflag          	*int64
	outputflag         	*string
	threadflag         	*int
	pauseflag          	*int64
	proxyflag          	*int64
	dockerflag         	*int
	successInheritflag 	*bool
	failureInheritflag 	*bool
)

func init() {
	// 标记当前init()已执行完毕
	defer cache.ExecInit(0)
}


func main () {
	if SignalProcess () {
		fmt.Printf("%s is running\n", config.FullName)
		return
	}
	// 解析命令行参数
	CommandLine()

	// 针对输入参数执行相应的命令行操作
	switch cache.Task.RunType {
	case status.DAEMON:
		daemon.NewDaemon().Run()
	case status.CONSOLE:
		fallthrough
	default:
	}

	exec.Run ()
}


func SignalProcess () bool {
	fp, err := os.OpenFile(config.PidFile, os.O_WRONLY | os.O_CREATE | os.O_TRUNC, os.ModePerm)
	if nil != err {
		fmt.Printf("open file error: %v\n", err)
		return true
	}
	defer fp.Close()

	err = syscall.Flock(int(fp.Fd()), syscall.LOCK_EX | syscall.LOCK_NB)
	if nil != err {
		fmt.Printf("lock file error:%v\n", err)
		return true
	}

	_, err = fp.WriteString(strconv.Itoa(os.Getpid()) + "\n")
	if nil != err {
		fmt.Printf("write pid error, process already exists")
		return true
	}

	return false
}

// 解析、初始化命令行参数
func CommandLine () {
	port = flag.Int(
		"port",
		cache.Task.Port,
		"   端口号: 只填写数字即可，不含冒号，单机模式不填")

	//主节点ip，客户端模式填写
	master = flag.String(
		"a_master",
		cache.Task.Master,
		"   <服务端IP: 不含端口，客户端模式下使用>")

	// 自定义配置
	keyinsflag = flag.String(
		"a_keyins",
		cache.Task.Keyins,
		"   <自定义配置: 多任务请分别多包一层“<>”>")

	// 采集上限
	limitflag = flag.Int64(
		"a_limit",
		cache.Task.Limit,
		"   <采集上限（默认限制URL数）> [>=0]")

	// 输出方式
	outputflag = flag.String(
		"a_outtype",
		cache.Task.OutType,
		func() string {
			var outputlib string
			for _, v := range app.LogicApp.GetOutputLib() {
				outputlib += "[" + v + "] "
			}
			return "   <输出方式: > " + strings.TrimRight(outputlib, " ")
		}())

	// 并发协程数
	threadflag = flag.Int(
		"a_thread",
		cache.Task.ThreadNum,
		"   <并发协程> [1~99999]")

	// 平均暂停时间
	pauseflag = flag.Int64(
		"a_pause",
		cache.Task.Pausetime,
		"   <平均暂停时间/ms> [>=100]")

	// 代理IP更换频率
	proxyflag = flag.Int64(
		"a_proxyminute",
		cache.Task.ProxyMinute,
		"   <代理IP更换频率: /m，为0时不使用代理> [>=0]")

	// 分批输出
	dockerflag = flag.Int(
		"a_dockercap",
		cache.Task.DockerCap,
		"   <分批输出> [1~5000000]")

	// 继承历史成功记录
	successInheritflag = flag.Bool(
		"a_success",
		cache.Task.SuccessInherit,
		"   <继承并保存成功记录> [true] [false]")

	// 继承历史失败记录
	failureInheritflag = flag.Bool(
		"a_failure",
		cache.Task.FailureInherit,
		"   <继承并保存失败记录> [true] [false]")

	// 特殊配置
	config.ServerPort = flag.Int("webPort", 8888, "信息浏览页port")
	config.ServerHost = flag.String("webHost", "0.0.0.0", "信息浏览页ip")

	runType = flag.String("runType", "console", "选择运行模式：后台运行(daemon)，控制台运行(console)")
	config.RunMode = flag.String("mode", "offline", "运行模式：单机(offline), 服务端(service), 客户端(client)")

	// 解析命令行参数
	flag.Parse()

	// 更新命令行参数
	switch *config.RunMode {
	case "standalone":
		cache.Task.Mode = status.OFFLINE
	case "service":
		cache.Task.Mode = status.SERVER
	case "client":
		cache.Task.Mode = status.CLIENT
	default:
		cache.Task.Mode = status.OFFLINE
	}

	cache.Task.Port = *port
	cache.Task.Master = *master

	// 运行类型
	switch *runType {
	case "daemon":
		cache.Task.RunType = status.DAEMON
	case "console":
		cache.Task.RunType = status.CONSOLE
	}

	cache.Task.Keyins = *keyinsflag
	cache.Task.Limit = *limitflag
	cache.Task.OutType = *outputflag
	cache.Task.ThreadNum = *threadflag
	cache.Task.Pausetime = *pauseflag
	cache.Task.ProxyMinute = *proxyflag
	cache.Task.DockerCap = *dockerflag
	cache.Task.SuccessInherit = *successInheritflag
	cache.Task.FailureInherit = *failureInheritflag
}
