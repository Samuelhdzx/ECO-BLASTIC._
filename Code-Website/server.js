
//---------------------------------------------------------------------------------------------
var fs = require('fs');
var url = require('url');
var http = require('http');
var querystring = require('querystring');
var db = []; //database
//---------------------------------------------------------------------------------------------
// function g?i yêu c?u(response) t? phía server ho?c nh?n yêu c?u (request) c?a client g?i lên
function requestHandler(request, response) {

    // Gi? s? d?a ch? nh?n du?c http://192.168.1.7:8000/update?temp=30&humd=40
    var uriData = url.parse(request.url);
    var pathname = uriData.pathname;          // /update?
    var query = uriData.query;                // temp=30.5&hum=80
    var queryData = querystring.parse(query); // queryData.temp = 30.5, queryData.humd = 40
    //-----------------------------------------------------------------------------------------
    if (pathname == '/update') {
        var newData = {
            temp: queryData.temp,
            humd: queryData.humd,
            time: new Date()
        };
        db.push(newData);
        console.log(newData);
        response.end();
    //-----------------------------------------------------------------------------------------
    } else if (pathname == '/get') {
        response.writeHead(200, {
            'Content-Type': 'application/json'
        });
        response.end(JSON.stringify(db));
        db = [];
    //-----------------------------------------------------------------------------------------
    } else { 
        fs.readFile('./index.html', function(error, content) {
            response.writeHead(200, {
                'Content-Type': 'text/html'
            });
            response.end(content);
        });
    }
    //-----------------------------------------------------------------------------------------
}
var server = http.createServer(requestHandler);
server.listen(8000); 
console.log('Server listening on port 8000');