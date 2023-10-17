package cache

import (
	"fmt"
	"os"
	"time"

	"gopkg.in/yaml.v3"
)

type Cache struct {
	LastBackupTime time.Time `yaml:"last_backup_time"`
}

func New() Cache {
	var cache Cache
	beginning := time.Date(1, 1, 1, 0, 0, 0, 0, time.UTC)
	cache_path := os.Getenv("HOME") + "/.cache/backuptool.cache"

	f, err := os.ReadFile(cache_path)
	if err != nil {
		panic(err)
	}

	yaml.Unmarshal(f, &cache)

	if cache.LastBackupTime == beginning {
		cache.LastBackupTime = time.Now()
	}

	fmt.Println(cache)

	return cache
}

func (c *Cache) UpdateLastBackupTime() {
	cache_path := os.Getenv("HOME") + "/.cache/backuptool.cache"

	c.LastBackupTime = time.Now()

	yaml, err := yaml.Marshal(c)
	if err != nil {
		panic(err)
	}

  err = os.WriteFile(cache_path, yaml, 0664)
  if err != nil {
    panic(err)
  }
}
