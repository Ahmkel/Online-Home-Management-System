(function () {

    //Create the Service
    var $GetSensorsService = function ($http) {
        var GetSensorsReadings = function () {
            //$http.get("WebsitePath/api/GetSensors/").then(err, function (response) {
            return $http.get("WebsitePath/api/GetSensors/").then(function (response) {
                return response.data;
            });
        };
        return {
            GetSensorsReadings: GetSensorsReadings
        };
    };

    //Get the Module
    var App = angular.module("HMS");
    //Register the Service
    App.factory("$GetSensorsService", $GetSensorsService);
} ());
