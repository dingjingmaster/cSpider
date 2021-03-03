package web

import (
	"log"
	"net/http"
	"os"
	"os/exec"
	"runtime"
	"spider/config"
	"strconv"
	"time"

	"spider/app"
	"spider/logs"
	"spider/runtime/cache"
)

var (
	addr       string
	spiderMenu []map[string]string
)

// 执行入口
func Run() {
	appInit()

	// web服务器地址
	addr = *config.ServerHost + ":" + strconv.Itoa(*config.ServerPort)

	// 预绑定路由
	Router()

	log.Printf("[%s] Server running on %v\n", config.NAME, addr)

	// 自动打开web浏览器
	var cmd *exec.Cmd
	switch runtime.GOOS {
	case "windows":
		cmd = exec.Command("cmd", "/c", "start", "http://localhost:"+strconv.Itoa(*config.ServerPort))
	case "darwin":
		cmd = exec.Command("open", "http://localhost:"+strconv.Itoa(*config.ServerPort))
	}
	if cmd != nil {
		go func() {
			log.Printf("[%s] Open the default browser after two seconds...\n", config.NAME)
			time.Sleep(time.Second * 2)
			cmd.Stdout = os.Stdout
			cmd.Stderr = os.Stderr
			cmd.Run()
		}()
	}

	// 监听端口
	err := http.ListenAndServe(addr, nil) //设置监听的端口
	if err != nil {
		logs.Log.Emergency("ListenAndServe: %v", err)
	}
}

func appInit() {
	app.LogicApp.SetLog(Lsc).SetAppConf("Mode", cache.Task.Mode)

	spiderMenu = func() (spmenu []map[string]string) {
		// 获取蜘蛛家族
		for _, sp := range app.LogicApp.GetSpiderLib() {
			spmenu = append(spmenu, map[string]string{"name": sp.GetName(), "description": sp.GetDescription()})
		}
		return spmenu
	}()
}
