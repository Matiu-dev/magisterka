job "postgres" {
  datacenters = ["dc1"]
  type = "service"

  group "postgres" {
    count = 1

    task "postgres" {
      driver = "docker"
      config {
        image = "postgres"
        ports = ["db", "http"]
      }
      env {
          POSTGRES_USER="postgres"
          POSTGRES_PASSWORD="admin"
      }

      logs {
        max_files     = 5
        max_file_size = 15
      }

      resources {
        cpu = 1000
        memory = 1024
      }
      service {
        name = "postgres"
        tags = ["postgres for vault"]
        port = "db"

        check {
          name     = "alive"
          type     = "tcp"
          interval = "10s"
          timeout  = "2s"
        }
      }

    }
    restart {
      attempts = 10
      interval = "5m"
      delay = "25s"
      mode = "delay"
    }
    network {
      mbits = 10
      port  "db"  {
        static = 5432
      }
      port "http" {
        to = 8080
      }
    }
  }
  update {
    max_parallel = 1
    min_healthy_time = "5s"
    healthy_deadline = "5m"
    auto_revert = false
    canary = 0
  }
}
