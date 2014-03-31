#Main script
import sys
import geojson
import datetime
from httplib2 import Http
from geopy import geocoders


class Arduino:
    def __init__(self, temperature, light, noise, humidity):
        self.temperature = temperature
        self.light = light
        self.noise = noise
        self.humidity = humidity
        self.id = ""
        self.location = "BCN-UPFPOBLENOU"
        self.datasetId = 'environmental'
        self.address = 'Sagrada Familia, Carrer de Mallorca, Barcelona'
        self.description = ''
        self.apikey = "7b1611c3-c688-474b-bcab-6e4921bfb109"
        g = geocoders.GoogleV3()
        place, (lat, lng) = g.geocode(self.address)
        self.latitud = lat
        self.longitud = lng
        #print "%s: %.5f, %.5f" % (place, lat, lng)


def collectdata():
    #1- Collect the data.
    print "Collecting the data from the arduino sensors"
    arduino = Arduino(sys.argv[2], sys.argv[3], sys.argv[4], sys.argv[5])
    arduino.id = sys.argv[1]
    print "Done collecting"
    return arduino


def readfile(arduino):
    #2- Read a file (logData) to check if the new value is the same as the last write value.
    #3- If the value is equal, the script will do nothing, if is different, it will write down in a new line on the file
    print "Reading the logData to check the id value"
    logData = open('logData', 'r')
    lastline = ""
    if not logData.read(1):
        arduino.id = 0
        prueba = '-' + str(arduino.id) + '-' + str(arduino.temperature) + '-' + str(arduino.humidity) \
                 + '-' + str(arduino.light) + '-' + str(arduino.noise)
    else:
        for line in logData:
            lastline = line

        p = lastline.split("-")
        arduino.id = int(p[0]) + 1
        prueba = '\n' + str(arduino.id) + '-' + str(arduino.temperature) + '-' + str(arduino.humidity) \
                 + '-' + str(arduino.light) + '-' + str(arduino.noise)

    logData.close()
    logData = open('logData', 'a')
    logData.write(prueba)
    logData.close()
    arduino.id += 1
    print "The new values had been added to the logData file"


def createJSON(arduino):
    #4- Create the GeoJSON.
    print "Creating the GeoJSON"
    timestamp = datetime.datetime.now().isoformat()

    p = geojson.FeatureCollection(
        name='Temperature Invented value1',
        timeStamp=timestamp,
        features=[
            geojson.Feature(
                id='d25830850271b4e90cc5dcdd0fb18daf',
                type='Feature',
                tags=['temperature', 'sensor', 'arduino', 'upf', 'guifi'],
                geometry=geojson.Point([arduino.longitud, arduino.latitud]),
                properties={
                    'id': "%s" % (arduino.id + ".1"),
                    'name': "%s" % ("SENSOR-TEMP" + arduino.location),
                    'datasetId': "%s" % arduino.datasetId,
                    'datasetName': "%s" % arduino.datasetId,
                    'address': "%s" % arduino.address,
                    'description': "%s" % ('Temperature sensor of ' + arduino.location),
                    'timeStamp': "%s" % timestamp,
                    'value': "%s" % arduino.temperature,
                    'unit': "%s" % 'Cel'
                }
            ),
            geojson.Feature(
                id='d25830850271b4e90cc5dcdd0fb18daf',
                type='Feature',
                tags=['noise', 'sensor', 'arduino', 'upf', 'guifi'],
                geometry=geojson.Point([arduino.longitud, arduino.latitud]),
                properties={
                    'id': "%s" % (arduino.id + ".3"),
                    'name': "%s" % ("SENSOR-NOISE" + arduino.location),
                    'datasetId': "%s" % arduino.datasetId,
                    'datasetName': "%s" % arduino.datasetId,
                    'address': "%s" % arduino.address,
                    'description': "%s" % ('Noise sensor of ' + arduino.location),
                    'timeStamp': "%s" % timestamp,
                    'value': "%s" % arduino.noise,
                    'unit': "%s" % 'x'
                }
            ),
            geojson.Feature(
                id='d25830850271b4e90cc5dcdd0fb18daf',
                type='Feature',
                tags=['humidity', 'sensor', 'arduino', 'upf', 'guifi'],
                geometry=geojson.Point([arduino.longitud, arduino.latitud]),
                properties={
                    'id': "%s" % (arduino.id + ".4"),
                    'name': "%s" % ("SENSOR-HUMIDITY" + arduino.location),
                    'datasetId': "%s" % arduino.datasetId,
                    'datasetName': "%s" % arduino.datasetId,
                    'address': "%s" % arduino.address,
                    'description': "%s" % ('Humidity sensor of ' + arduino.location),
                    'timeStamp': "%s" % timestamp,
                    'value': "%s" % arduino.humidity,
                    'unit': "%s" % '%'
                }
            ),
            geojson.Feature(
                id='d25830850271b4e90cc5dcdd0fb18daf',
                type='Feature',
                tags=['light', 'sensor', 'arduino', 'upf', 'guifi'],
                geometry=geojson.Point([arduino.longitud, arduino.latitud]),
                properties={
                    'id': "%s" % (arduino.id + ".2"),
                    'name': "%s" % ("SENSOR-LIGHT" + arduino.location),
                    'datasetId': "%s" % arduino.datasetId,
                    'datasetName': "%s" % arduino.datasetId,
                    'address': "%s" % arduino.address,
                    'description': "%s" % ('Light sensor of ' + arduino.location),
                    'timeStamp': "%s" % timestamp,
                    'value': "%s" % arduino.light,
                    'unit': "%s" % 'lux'
                }
            )

        ]
    )
    data = geojson.dumps(p)
    data = data.replace(" \"id\": \"d25830850271b4e90cc5dcdd0fb18daf\", ", " ")
    #print data

    print "Done creating the GeoJSON"
    return data
    #Validar GeoJSON


def POSTopencities(arduino, data):
    #5- Do the POST to opencities.

    #data = json.dumps(p, encoding='utf8', sort_keys=True)

    print "Sending the data to opencities"
    http_obj = Http()
    resp, content = http_obj.request(
        uri="http://opencities.upf.edu/osn2/api/datasets/uploadGeoJson/" + arduino.apikey + "/" + arduino.datasetId,
        #uri="http://opencities.upf.edu/osn2/api/datasets/uploadGeoJson/7b1611c3-c688-474b-bcab-6e4921bfb109/temperature",
        method='POST',
        headers={'Content-Type': 'application/json; charset=UTF-8'},
        #body=dumps(dictionary),
        body=data
    )
    print "Response from opencities:"
    print resp






def main():
    if len(sys.argv) != 6:
        print "Usage: python main.py id temperature light noise humidity"
        print "And you write: " + str(sys.argv)
        sys.exit(0)

    arduino = collectdata()
    print "ha acabado de recolectar los datos"
    #readfile(arduino)
    data = createJSON(arduino)
    POSTopencities(arduino, data)


if __name__ == '__main__':
    main()
else:
    pass








