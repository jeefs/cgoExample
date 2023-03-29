package main

import "testing"

func BenchmarkRandString(b *testing.B) {
	b.ResetTimer()
	test02()
	b.StopTimer()
}
