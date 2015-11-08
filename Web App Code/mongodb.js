var mongodb=require('mongodb');

var seedData = [{ value: 0}];

var uri = "mongodb://admin:admin@ds047642.mongolab.com:47642/mongodb_test1";

mongodb.MongoClient.connect(uri, function (err, db) {
    if (err) throw err;

    var Info = db.collection('Info');

    Info.insert(seedData);
});