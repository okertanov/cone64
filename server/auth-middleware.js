//
// Copyright (C) 2017 Oleg Kertanov <okertanov@gmail.com>
//

(function() {

    "use strict";

    //
    // AuthMiddleware
    //
    var AuthMiddleware = function() {
        return {
            _server: null,
            //
            // Initializer
            //
            Initialize: function(server) {
                this._server = server;
            },
            //
            // Request handler: '*'
            //
            AllRequests: function() {
                var that = this;
                return function(req, res, next) {
                    that._server.Log('Auth: ', req.path, req.ip);
                    next();
                }
            },
            //
            // Auth Error handler
            //
            OnError: function() {
                var that = this;
                return function(err, req, res, next) {
                    that._server.Log('Unexpected auth error with request: ', req.path, err, err.stack);
                    res.sendStatus(500);
                }
            }
        };
    };

    //
    // AuthMiddlewareError
    //
    function AuthMiddlewareError(what) {
        this.name = 'AuthMiddlewareError';

        if (!what) {
            this.message = 'Unknown Auth Middleware API Module Error';
        }
        else if (what instanceof Error && what.message) {
            this.message = what.message;
            this.fileName = what.fileName;
            this.lineNumber = what.lineNumber;
            this.columnNumber = what.columnNumber;
            this.stack = what.stack;
        }
        else {
            this.message = what;
        }
    }
    AuthMiddlewareError.prototype = Object.create(Error.prototype);
    AuthMiddlewareError.prototype.constructor = AuthMiddlewareError;

    //
    // Module Exports
    //
    module.exports = AuthMiddleware;

})();
