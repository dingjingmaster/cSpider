package gold_price

import (
	"encoding/json"
	"fmt"
	"spider/app/downloader/request"
	. "spider/app/spider"
	_ "spider/common/goquery"
	"spider/common/timeUtils"
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
				Url:"https://data-asg.goldprice.org/dbXRates/CNY",
				Rule: "获取标准黄金价格",
				Temp: map[string]interface {} {
					"target":"first",
				},
			})
		},

		Trunk: map[string]*Rule{
			"获取标准黄金价格": {
				ItemFields: []string {
					"id",
					"gold-1",
					"gold-2",
					"gold-h",
					"gold-l",
					"gold-v",
					"gold-a",
					"gold-t",
				},
				ParseFunc: func(ctx *Context) {
					jsonStr := ctx.GetText()
					gs := &GoldPriceStruct{}
					json.Unmarshal([]byte(jsonStr), &gs)
					gold1 := gs.Items[0].XauPrice
					gold2 := gs.Items[0].XauPrice
					goldh := gs.Items[0].XauPrice
					goldl := gs.Items[0].XauPrice
					goldv := gs.Items[0].ChgXau
					golda := 0
					goldt := timeUtils.GetTimeStamp()
					id := fmt.Sprintf("%d-%.2f-%.2f-%.2f-%.2f-%.2f-%d", goldt, gold1, gold2, goldh, goldl, goldv, golda)

					ctx.Output (map[int]interface{} {
						0: id,
						1: gold1,
						2: gold2,
						3: goldh,
						4: goldl,
						5: goldv,
						6: golda,
						7: goldt,
					})
					logs.Log.Informational("%v", id)
				},
			},
		},
	},
}