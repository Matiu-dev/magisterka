job "pytechco-redis" {
  type = "service"

  group "ptc-redis" {
    count = 1
    network {
      port "redis" {
        to = 5050
      }
    }

    service {
      name     = "redis-svc"
      port     = "redis"
      provider = "nomad"
    }

    task "redis-task" {
      driver = "docker"

      config {
        image = "dpage/pgadmin4:6.7"
        ports = ["redis"]
      }

      env {
        REDIS_USERNAME = "your_username"
        REDIS_PASSWORD = "your_password"
      }
    }
  }
}
