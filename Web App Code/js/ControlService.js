(function () {
    var $ControlService = function ($http) {
        var SetControl = function (Lights, DoorLock, Windows) {
            $http.get("WebsitePath/api/SetControl/Lights/" + Lights);
            $http.get("WebsitePath/api/SetControl/DoorLock/" + DoorLock);
            $http.get("WebsitePath/api/SetControl/Windows/" + Windows);
        };
        var GetControl = function () {
            return $http.get("WebsitePath/api/GetControl/").then(function (response) {
                return response.data;
            });
        };
        return {
            SetControl: SetControl,
            GetControl: GetControl
        };
    };
    //Get the Module
    var App = angular.module("HMS");
    //Register the Service
    App.factory('$ControlService', $ControlService);
} ());