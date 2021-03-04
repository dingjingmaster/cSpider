package user

import "spider/logs"

type UserInfo struct {
	LoginTime   int
	LoginHandle string
}

var AllUsers 	map[string] *UserInfo

func init () {
	logs.Log.Debug("初始化用户模块...")
}

