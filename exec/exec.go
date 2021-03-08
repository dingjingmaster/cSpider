package exec

import (
	"runtime"
	"spider/app"
	"spider/app/spider"
	"spider/common/gc"
)

func init() {
	runtime.GOMAXPROCS(runtime.NumCPU()) 				// 开启最大核心数运行
	gc.ManualGC()										// 开启手动GC
}

func Run () {
	// 启动网页显示服务

	// 启动爬虫任务
	RunSpider()

	// 启动所有 spider
	//for true {
	//	;
	//}

	// 开始运行
	//ctrl := make(chan os.Signal, 1)
	//signal.Notify(ctrl, os.Interrupt, os.Kill)
	//go web.Run()
	//<-ctrl
}

// FIXME:// 此处需要根据命令行进行配置
// 启动 spider
func RunSpider() {
	app.LogicApp.Init()

	// 初始化爬虫参数
	app.LogicApp.SetAppConf("ThreadNum", 20)
	app.LogicApp.SetAppConf("Pausetime", int64(200))
	app.LogicApp.SetAppConf("ProxyMinute", int64(0))
	app.LogicApp.SetAppConf("OutType", "csv")
	app.LogicApp.SetAppConf("DockerCap", 0)
	app.LogicApp.SetAppConf("Limit", int64(0))
	app.LogicApp.SetAppConf("Keyins", "")
	app.LogicApp.SetAppConf("SuccessInherit", true)					// 保存成功记录否
	app.LogicApp.SetAppConf("FailureInherit", true)					// 保存失败记录否

	GetAllSpider()

	app.LogicApp.Run()
}

// 扫描爬虫
func GetAllSpider () {
	var spiders []*spider.Spider
	for _, sp := range app.LogicApp.GetSpiderLib() {
		spiders = append(spiders, sp.Copy())
	}
	app.LogicApp.SpiderPrepare(spiders)
}