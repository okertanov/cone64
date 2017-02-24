//
// Copyright (C) 2017 Oleg Kertanov <okertanov@gmail.com>
//

(function() {

    "use strict";

    var Server = require("./Server");

    var server = new Server();

    server.Initialize();
    server.InitRoutes();
    server.Listen();

})();
