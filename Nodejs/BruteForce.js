var fs =  require('fs');
var md5 = require('md5');

var tab = ['a','b','c','d','e','f','g','h','i','j','k',
	   'l','m','n','o','p','q','r','s','t','u','v',
	   'w','x','y','z',
	   '0','1','2','3','4','5','6','7','8','9',
	   '!','@','#','$','%','&','*'];
var dicoSer = {};
var dicoDes = {};
var res = [];

function getString(input, rang, length) {
    var str = "";

    var tmp, inst = input;
    for (var i = 0; i < length; i++) {
	tmp = Math.floor(inst / rang);
	str += tab[Math.floor(inst - (tmp * rang)) % rang];
	inst = tmp;
    }
    return str;
};

function checkPWD(pass, tabPass) {
    passTmp = md5(pass);
    for (var i = 0; i < tabPass.length; i++) {
	if (passTmp == tabPass[i])
	    return tabPass[i];
    }
    return null; 
}

function bruteForce(res) {
    var len = 8;
    var max = Math.pow(tab.length, len);

    for (var iter = 0; iter < max ; iter++) {
	var str = getString(iter, tab.length, len);
	if ((hash = checkPWD(str, res)) != null) {
	    console.log(str + " >>  " + hash);
	}
    }
    console.log("fin");
};

fs.readFile('./dico', function read(err, data) {
    console.log(data);
    var lines = data.toString('utf-8').split('\n');
    for (nb in lines) {
	var tmp = md5(lines[nb]);
	dicoSer[lines[nb]] = tmp;
	dicoDes[tmp] = lines[nb];
    }
    fs.readFile('./input', function read(err, data) {
	console.log(data);
	var lines = data.toString('utf-8').split('\n');
	for (nb in lines) {
	    if (dicoDes[lines[nb]]) {
		console.log(lines[nb] + " >> " + dicoDes[lines[nb]]);
	    } else {
		res.push(lines[nb]);
	    }
    	}	
	bruteForce(res);
    });
});
