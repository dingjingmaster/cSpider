package web

import (
	"io/ioutil"
	"net/http"
	"text/template"

	"spider/app"
	"spider/common/session"
	"spider/config"
	"spider/logs"
	"spider/runtime/status"
)

var globalSessions *session.Manager

func init() {
	globalSessions, _ = session.NewManager("memory",
		`{
					"cookieName":"spiderSession",
					"enableSetCookie,omitempty": true,
					"secure": false,
					"sessionIDHashFunc": "sha1",
					"sessionIDHashKey": "",
					"cookieLifeTime": 157680000,
					"providerConfig": ""
				}`)
	// go globalSessions.GC()
}

// 处理web页面请求
func IndexHandle (rw http.ResponseWriter, req *http.Request) {
	sess, _ := globalSessions.SessionStart(rw, req)
	defer sess.SessionRelease(rw)
	//index, _ := views_index_html()
	//t, err := template.New("index").Parse(string(index)) //解析模板文件
	t, err := template.ParseFiles("web/views/index.html") //解析模板文件
	if err != nil {
		logs.Log.Error("%v", err)
	}

	data := map[string]interface{}{
		"title":   config.FullName,
		"logo":    config.IconPng,
		"version": config.VERSION,
		"author":  config.AUTHOR,
		"mode": map[string]int{
			"offline": status.OFFLINE,
			"server":  status.SERVER,
			"client":  status.CLIENT,
			"unset":   status.UNSET,
			"curr":    app.LogicApp.GetAppConf("mode").(int),
		},
		"status": map[string]int{
			"stopped": status.STOPPED,
			"stop":    status.STOP,
			"run":     status.RUN,
			"pause":   status.PAUSE,
		},
		"port": app.LogicApp.GetAppConf("port").(int),
		"ip":   app.LogicApp.GetAppConf("master").(string),
	}
	t.Execute(rw, data) //执行模板的merger操作
}

func LoginHandle (rw http.ResponseWriter, req *http.Request) {
	body, _ := ioutil.ReadAll(req.Body)
	logs.Log.Informational (string(body))

	//user.AllUsers["a"] = &user.UserInfo {
	//	LoginTime:   0,
	//	LoginHandle: "",
	//}
	rw.Write([]byte("ok"))
}

func SpiderHandle (rw http.ResponseWriter, req *http.Request) {
	body, _ := ioutil.ReadAll(req.Body)
	logs.Log.Informational (string(body))
}