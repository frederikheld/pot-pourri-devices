'use strict'

var app = require('./app.js')

const port = 8080

app.listen(port, () => {
    console.log('listening on localhost:' + port)
})