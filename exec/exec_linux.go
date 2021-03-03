package exec

import (
	"os"
	"os/exec"
	"os/signal"

	"spider/config"
	"spider/web"
)

func run() {
	exec.Command("/bin/sh", "-c", "title", config.FullName).Start()

	ctrl := make(chan os.Signal, 1)
	signal.Notify(ctrl, os.Interrupt, os.Kill)
	go web.Run()
	<-ctrl
}
