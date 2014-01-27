#Main script
import sys
import geojson
import datetime
import httplib
import urllib

ID = 0
temperature = int(sys.argv[1])
#1- Collect the data.

if len(sys.argv) != 2:
    print "Usage: python main.py temperature"
    print "And you write: " + str(sys.argv)
    sys.exit(0)

#2- Read a file (logData) to check if the new value is the same as the last writed value.
#3- If the value is equal, the script will do nothing, if is different, it will write down in a new line on the file.
print "Reading the logData to check if the new values are new"
logData = open('logData', 'r')

if not logData.read(1):
    ID = 0
else:
    for line in logData:
        lastLine = line

    p = lastLine.split("-")
    ID = int(p[0]) + 1

#print ID
if ID != 0:
    if temperature == int(p[1]):
        print "The temperature has not change since last update"
    else:
        logData.close()
        logData = open('logData', 'a')
        logData.write('\n'+str(ID) + '-' + str(temperature))
        ID += 1
        print "The new value of temperature has been added to the logData file"

else:
    logData.close()
    logData = open('logData', 'a')
    logData.write('-'+str(ID) + '-' + str(temperature))
    ID += 1
    print "The new value of temperature has been added to the logData file"

#4- Create the GeoJSON.
timestamp = datetime.datetime.now().isoformat()

p = geojson.FeatureCollection(
    name='Temperature Invented value1',
    timestamp=timestamp,
    features=[
        geojson.Feature(
            type='Feature',
            tags=['red', 'tall', 'cheap'],
            geometry=geojson.Point([2.167028, 41.387547]),
            properties={
                'id': "%s" % ID,
                'name': "%s" % 'SENSOR-TEMP-BCN-UPFPOBLENOU',
                'datasetId': "%s" % 'temperature',
                'datasetName': "%s" % 'temperature',
                'address': "%s" % 'Carrer de Tanger, Barcelona',
                'description': "%s" % 'Temperature sensor of UPF Poblenou',
                'timeStamp': "%s" % timestamp,
                'value': "%s" % temperature,
                'unit': "%s" % '*C'
                #'contentType': "%s" % 'video/ogg',
                #'url': "%s" % 'http://download.blender.org/peach/trailer/trailer_1080p.ogg',
                #'previewImage': "%s" % 'http://peach.blender.org/wp-content/uploads/poster_rodents_small.jpg'
            }
        )

    ]
)
data = geojson.dumps(p)
print data

#5- Do the POST to opencities.
print "Sending the data to opencities"


params = urllib.urlencode(data)
headers = {"Content-type": "application/json"}
conn = httplib.HTTPConnection("http://opencities.upf.edu")
conn.request("POST", "/osn2/api/datasets/uploadGeoJson/7b1611c3-c688-474b-bcab-6e4921bfb109/temperature", params, headers)
response = conn.getresponse()
print response.status, response.reason
















