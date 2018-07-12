'use strict'

var exports = module.exports = {}

exports.foo = (string) => {
    return new Promise((resolve, reject) => {
        resolve(string)
    })
}

exports.promiseAll = () => {

    var p1 = new Promise((resolve, reject) => {
        resolve("1")
    })

    var p2 = new Promise((resolve, reject) => {
        resolve("2")
    })

    var p3 = new Promise((resolve, reject) => {
        reject("3")
    })

    return Promise.all([p1, p2, p3])
}