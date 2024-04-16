 job "nbpapp8093" {
  datacenters = ["dc1"]
  type        = "service"

  group "web" {
    count = 1

    network {
      port "quarkus"
      {
        to = 8093
      }
    }

    task "service" {
      driver = "docker"

      config {
        image        = "matiuw/nbp-app8093:latest"
        network_mode = "host"
        ports        = ["quarkus"]
      }
    }
  }
}
