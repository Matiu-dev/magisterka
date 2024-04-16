job "pgadmin-job" {
  datacenters = ["dc1"]

  group "pgadmin-g" {
    count = 1

    network {
      port "pgadmin" {
        static = 5050
      }
    }

    service {
      name = "pgadmin-svc"
      port = "pgadmin"
      tags = ["pgadmin"]
    }

    task "pgadmin-task" {
      driver = "docker"

      config {
        image = "dpage/pgadmin4:6.7"
        port_map {
          pgadmin = 5050
        }

        env {
          PGADMIN_DEFAULT_EMAIL    = "admin@admin.com"
          PGADMIN_DEFAULT_PASSWORD = "admin"
        }
      }

      resources {
        cpu    = 500 # or whatever value is appropriate
        memory = 256 # or whatever value is appropriate
      }
    }
  }
}
