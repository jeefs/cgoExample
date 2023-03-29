package main

type DecryptData struct {
	Index          int    `json:"index"`   // 索引
	Mac            string `json:"mac"`     // mac地址
	Current        int    `json:"current"` // 电流值1
	Temp           int    `json:"temp"`    // 温度值
	TempWarning    int    `json:"twarn"`   // 温度值报警
	Battery        int    `json:"dump"`    // 电量值
	Reindex        int    `json:"reindex"` // 剩余笔数
	GlucoseValue   int    `json:"glouse"`  // 血糖值
	GlucoseTrend   int    `json:"trend"`   // 血糖趋势
	GlucoseWarning int    `json:"gwarn"`   // 血糖报警
	CurrentWarning int8   `json:"cwarn"`   // 电流报警
	CreateTime     int64  `json:"itime"`   // 时间戳，精确到毫秒
}
