 job "nbpapp8094" {
  datacenters = ["dc1"]
  type        = "service"

  group "web" {
    count = 1

    network {
      port "quarkus"
      {
        to = 8094
      }
    }

    task "service" {
      driver = "docker"

      config {
        image        = "matiuw/nbp-app8094:latest"
        network_mode = "host"
        ports        = ["quarkus"]
      }
    }
  }
}
