package user

import (
	"spider/logs"
	"sync"
	"time"
)

type UserSession struct {
	sync.Mutex
	allUsers 		map[string]*UserInfo
}

type UserInfo struct {
	loginTime   int64
	// 保存的一些信息
}

var GAllUsers = newUser ()

func init () {
	logs.Log.Debug("初始化用户模块...")
}

func newUser () *UserSession {
	return &UserSession {
		allUsers : map[string]*UserInfo{},
	}
}

func (self *UserSession) NewUser (userName string) {
	self.Lock()
	defer self.Unlock()

	userInfo := UserInfo {time.Now().Unix()}

	self.allUsers[userName] = &userInfo
}