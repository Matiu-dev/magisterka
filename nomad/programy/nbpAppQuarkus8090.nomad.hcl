 job "nbpapp8090" {
  datacenters = ["dc1"]
  type        = "service"

  group "web" {
    count = 1

    network {
      port "quarkus"
      {
        to = 8090
      }
    }

    task "service" {
      driver = "docker"

      config {
        image        = "matiuw/nbp-app8090:latest"
        network_mode = "host"
        ports        = ["quarkus"]
      }
    }
  }
}
