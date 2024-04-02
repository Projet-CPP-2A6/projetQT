import QtQuick 2.0
import QtQuick.Window 2.0
import QtLocation 5.6
import QtPositioning 5.6
//import QtQuick.Controls 2.12 // Ou une autre version antérieure qui fonctionne pour vous



Window {
    width: 1000
    height: 850
    visible: true

    Plugin {
        id: mapPlugin
        name: "osm"
        PluginParameter {
            name: "osm.mapping.providersrepository.disabled"
            value: "true"
        }
        PluginParameter {
            name: "osm.mapping.providersrepository.address"
            value: "http://maps-redirect.qt.io/osm/5.6/"
        }
    }

    Map {
        id: map
        anchors.fill: parent
        plugin: mapPlugin
        center: QtPositioning.coordinate(36.81607972567222, 10.173058664699317) // Tunis
        zoomLevel: 8

        ListModel {
            id: locationModel
                     ListElement { name: "Tunis"; latitude: 36.8061; longitude: 10.1711 }
                      ListElement { name: "Ariana"; latitude: 36.8663; longitude: 10.1647 }
                      ListElement { name: "Béja"; latitude: 36.7246; longitude: 9.1817 }
                      ListElement { name: "Ben Arous"; latitude: 36.7555; longitude: 10.2049 }
                      ListElement { name: "Bizerte"; latitude: 37.2732; longitude: 9.8772 }
                      ListElement { name: "Gabès"; latitude: 33.8811; longitude: 10.0982 }
                      ListElement { name: "Gafsa"; latitude: 34.4328; longitude: 8.7787 }
                      ListElement { name: "Jendouba"; latitude: 36.5017; longitude: 8.7807 }
                      ListElement { name: "Kairouan"; latitude: 35.6804; longitude: 10.1015 }
                      ListElement { name: "Kasserine"; latitude: 35.1677; longitude: 8.8289 }
                      ListElement { name: "Kébili"; latitude: 33.7076; longitude: 8.9717 }
                      ListElement { name: "Kef"; latitude: 36.1573; longitude: 8.7065 }
                      ListElement { name: "Mahdia"; latitude: 35.5037; longitude: 11.056 }
                      ListElement { name: "Manouba"; latitude: 36.8063; longitude: 9.8506 }
                      ListElement { name: "Médenine"; latitude: 33.3528; longitude: 10.4923 }
                      ListElement { name: "Monastir"; latitude: 35.7836; longitude: 10.8256 }
                      ListElement { name: "Nabeul"; latitude: 36.4612; longitude: 10.7341 }
                      ListElement { name: "Sfax"; latitude: 34.7406; longitude: 10.7604 }
                      ListElement { name: "Sidi Bouzid"; latitude: 35.0393; longitude: 9.4918 }
                      ListElement { name: "Siliana"; latitude: 36.0849; longitude: 9.3727 }
                      ListElement { name: "Sousse"; latitude: 35.8254; longitude: 10.636 }
                      ListElement { name: "Tataouine"; latitude: 32.9297; longitude: 10.4518 }
                      ListElement { name: "Tozeur"; latitude: 33.9196; longitude: 8.1336 }
                      ListElement { name: "Zaghouan"; latitude: 36.4017; longitude: 10.1448 }
                      ListElement { name: "Djerba"; latitude: 33.7922; longitude: 10.7711 }
                      ListElement { name: "Zarzis"; latitude: 33.5072; longitude: 11.0979 }
                      ListElement { name: "Ben Guerdane"; latitude: 33.131438415071784; longitude: 11.210434152931263 }
                      ListElement { name: "La Marsa"; latitude: 36.8841; longitude: 10.3215 }
                      // Add more locations as needed
                  }

        // MapItemView to display locations
        MapItemView {
            model: locationModel

            delegate: MapQuickItem {
                coordinate: QtPositioning.coordinate(model.latitude, model.longitude)
                anchorPoint.x: image.width / 2
                anchorPoint.y: image.height
                sourceItem: Item {
                    width: 32
                    height: 32

                    Rectangle {
                        width: 10
                        height: 10
                        color: "red"
                        opacity: 1

                        MouseArea {
                            anchors.fill: parent
                            onClicked: console.log("Clicked on " + model.name)


                        }


                            }

}
}
}
}
}
