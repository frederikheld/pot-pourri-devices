'use strict'

const chai = require('chai')
const expect = chai.expect
const chaiHttp = require('chai-http')

chai.use(chaiHttp)

const app = require('../app.js')

describe('Hello World route', () => {

    it('returns 200', () => {
        chai.request(app)
            .get('/')
            .end((err, res) => {
                if (err) done(err)
                expect(res).to.have.status(200)
            })
    })

    it('returns a "Hello World" message', () => {
        chai.request(app)
            .get('/')
            .end((err, res) => {
                if (err) done(err)
                expect(res.body.message).to.be.equal('Hello World!')
            })
    })

})