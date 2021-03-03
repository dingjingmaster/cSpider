package web

import (
	"flag"
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
	ip         *string
	port       *int
	addr       string
	spiderMenu []map[string]string
)

// 获取外部参数
func Flag() {
	flag.String("b ******************************************** only for web ******************************************** -b", "", "")
	// web服务器IP与端口号
	ip = flag.String("b_ip", "0.0.0.0", "   <Web Server IP>")
	port = flag.Int("b_port", 9090, "   <Web Server Port>")
}

// 执行入口
func Run() {
	appInit()

	// web服务器地址
	addr = *ip + ":" + strconv.Itoa(*port)

	// 预绑定路由
	Router()

	log.Printf("[%s] Server running on %v\n", config.NAME, addr)

	// 自动打开web浏览器
	var cmd *exec.Cmd
	switch runtime.GOOS {
	case "windows":
		cmd = exec.Command("cmd", "/c", "start", "http://localhost:"+strconv.Itoa(*port))
	case "darwin":
		cmd = exec.Command("open", "http://localhost:"+strconv.Itoa(*port))
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
