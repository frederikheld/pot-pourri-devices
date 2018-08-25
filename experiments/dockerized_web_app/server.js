'use strict'

const PORT = 3333

const express = require('express')

const app = express()
app.get('/', (requestAnimationFrame, res) => {
    res.send("Hello World!\n")
})
app.get('/hello', (requestAnimationFrame, res) => {
    res.send("Hello Stranger!\n")
})
app.listen(PORT)
console.log("Receive a friendly hello by calling GET on 'http://localhost:" + PORT + "/hello'")