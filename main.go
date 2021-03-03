package main

import (
	"spider/exec"
	_ "spider/spiders" // 此为公开维护的spider规则库
)

func main () {
	//daemon.Background(true)

	// 子进程执行的内容
	exec.DefaultRun ()
}
