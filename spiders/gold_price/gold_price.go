package gold_price

import (
	"encoding/json"
	"spider/app/downloader/request"
	. "spider/app/spider"
	_ "spider/common/goquery"
	"spider/logs"
)

func init() {
	GoldPrice.Register()
}

type GoldPriceStruct struct {
	Ts int64 `json:"ts"`
	Tsj int64 `json:"tsj"`
	Date string `json:"date"`
	Items [] struct {
		Curr string `json:"curr"`
		XauPrice float64 `json:"xauPrice"`
		XagPrice float64 `json:"xagPrice"`
		ChgXau float64 `json:"chgXau"`
		ChgXag float64 `json:"chgXag"`
		PcXau float64 `json:"pcXau"`
		PcXag float64 `json:"pcXag"`
		XauClose float64 `json:"xauClose"`
		XagClose float64 `json:"xagClose"`
	} `json:"items"`
}

var GoldPrice = &Spider {
	Name: "金价获取",
	Description: "金价获取",
	Pausetime: 300,
	Limit:        LIMIT,
	EnableCookie: false,
	RuleTree: &RuleTree{
		Root: func(ctx *Context) {
			ctx.AddQueue(&request.Request{
				Url:"https://data-asg.goldprice.org/dbXRates/USD,CNY",
				Rule: "获取中国和美国黄金价格",
				Temp: map[string]interface {} {
					"target":"first",
				},
			})
		},

		Trunk: map[string]*Rule{
			"获取中国和美国黄金价格": {
				ParseFunc: func(ctx *Context) {
					jsonStr := ctx.GetText()
					gs := &GoldPriceStruct{}
					json.Unmarshal([]byte(jsonStr), &gs)
					logs.Log.Informational("country:%s, price:%f, date:%s", gs.Items[0].Curr, gs.Items[0].ChgXau, gs.Date)
				},
			},
		},
	},
}