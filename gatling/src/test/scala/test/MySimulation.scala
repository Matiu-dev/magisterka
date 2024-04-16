package test

import io.gatling.core.Predef._
import io.gatling.http.Predef._

class MySimulation extends Simulation {

  //protocol
  val httpProtocol = http
    .baseUrl("http://localhost:8080")

  //scenario
  val scn1 = scenario("Przelicz kurs").exec(
    http("Przelicz kurs req")
      .get("/currency/getCurrency/table/A/value/1")
      .header("content-type", "application/json")
      .asJson
//      .body(StringBody(
//        """
//          |{
//          |      "amount": 1,
//          |      "myCurrency": "USD",
//          |      "targetCurrency": "PLN"
//          |}
//          |""".stripMargin)).asJson
      .check(
        status is 200,
        jsonPath("$.code") is "BGN"
      )
  )

  //setup
  setUp(scn1.inject(rampUsers(6000).during(30))
  ).protocols(httpProtocol)


}
