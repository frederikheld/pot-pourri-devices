'use strict'

var express = require('express')
var path = require("path")


// -- config

var port = 3002


// -- publish web interface (client)

function publish_webinterface() {
    var app = express()

    app.use(express.static(path.join(__dirname, "web")))
    app.get("/", function (request, result) {
        result.sendFile(path.join(__dirname, "web", "index.html"))
    })

    app.listen(port, () => console.log("ui listening on port " + port))
}
publish_webinterface()