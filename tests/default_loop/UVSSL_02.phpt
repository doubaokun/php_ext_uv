--TEST--
Check for UVSSL Connect
--FILE--
<?php
$html = '';
$host = gethostbyname('github.com');
$loop = UVLoop::defaultLoop();
$ssl = new UVSSL($loop);
$ssl->connect($host, 443, function($ssl) use(&$html){
    $ssl->setSSLHandshakeCallback(function($ssl, $status) use(&$html){
        echo "handshake: ok\n";
        $request = "GET /RickySu/php_ext_uv HTTP/1.0\r\nUser-Agent: UVSSL\r\nAccept: */*\r\nHost: github.com\r\n\r\n";
        $ssl->write($request);
        return true;
    });
});
$ssl->setCallback(function($ssl, $recv) use(&$html){
    $html.=$recv;
}, function(){}, function($ssl) use(&$html){
    if(($pos = strpos($html, "\r\n\r\n")) !== false){
       $header = substr($html, 0, $pos);
       preg_match('/Status:\s(\d+)/i', $header, $match);
       echo "http status: {$match[1]}\n";
    }
    $ssl->close();
});
$loop->run();
?>
--EXPECT--
handshake: ok
http status: 200
