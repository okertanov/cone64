//
// Copyright (C) 2017 Oleg Kertanov <okertanov@gmail.com>
//

(function() {

    "use strict";

    var request = require('request');
    var ZmqApi = require('./ZmqApi').ZmqApi;
    var ZmqMessage = require('./ZmqApi').ZmqMessage;

    //
    // RequestMiddleware
    //
    var RequestMiddleware = function() {
        return {
            _server: null,
            _zmq_api: new ZmqApi(),
            //
            // Initializer
            //
            Initialize: function(server) {
                this._server = server;

                // ZmqApi
                this._zmq_api.Initialize({ bind_id: 'cone::global' });
                this._zmq_api.RegisterSubscriber('cone::metrics', this.OnQueueConeMetrics());
                this._zmq_api.RegisterSubscriber('cone::myip', this.OnQueueConeMyip());
                this._zmq_api.RegisterSubscriber('cone::uname', this.OnQueueConeUname());
            },
            //
            // Request handler: 'GET /'
            //
            GetRoot: function() {
                var that = this;
                return function(req, res, next) {
                    that._server.Log('Request: ', req.path, req.ip);
                    // Send 403 Forbidden
                    res.sendStatus(403);
                }
            },
            //
            // Request handler: 'GET /connect'
            //
            GetConnect: function() {
                var that = this;
                return function(req, res, next) {
                    that._server.Log('Request: ', req.path, req.ip);
                    // Send 401 Unauthorized
                    res.sendStatus(401);
                }
            },
            //
            // Request handler: 'GET /status'
            //
            GetStatus: function() {
                var that = this;
                return function(req, res, next) {
                    that._server.Log('Request: ', req.path, req.ip);
                    res.send('STATUS: OK');
                }
            },
            //
            // Request handler: 'GET /admin'
            //
            GetAdmin: function() {
                var that = this;
                return function(req, res, next) {
                    that._server.Log('Request: ', req.path, req.ip);
                    // Send 401 Unauthorized
                    res.sendStatus(401);
                }
            },
            //
            // Request handler: 'POST /ping'
            //
            PostPing: function() {
                var that = this;
                return function(req, res, next) {
                    that._server.Log('Request: ', req.path, req.ip, req.body);
                    var txt_response = 'pong';
                    res.send(txt_response);
                }
            },
            //
            // Error handler
            //
            OnError: function() {
                var that = this;
                return function(err, req, res, next) {
                    that._server.Log('Unexpected error with request: ', req.path, err, err.stack);
                    res.sendStatus(500);
                }
            }
        };
    };

    //
    // Module Exports
    //
    module.exports = RequestMiddleware;

})();
