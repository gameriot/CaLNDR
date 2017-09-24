import urllib.request, urllib.parse, urllib.error
import json

# Note that Google is increasingly requiring keys
# for this API
serviceurl = 'https://maps.googleapis.com/maps/api/distancematrix/json?units=imperial&'

f = open('backend.txt','r')









while True:
    start = input('Enter location: ')
    end = input('Enter location: ')
    if len(start) < 1: break
    if len(end) < 1: break

    url = serviceurl + urllib.parse.urlencode(
        {'destinations':end,'origins':start,'key':'AIzaSyAWWMJ3BOFBJbJBvkTo_z0wkUDBqPwhyjY'})
    print('Retrieving', url)

    uh = urllib.request.urlopen(url)
    data = uh.read().decode()
    print('Retrieved', len(data), 'characters')

    try:
        js = json.loads(data)
    except:
        js = None


    if not js or 'status' not in js or js['status'] != 'OK':
        #print('==== Failure To Retrieve ====')
        #print(data)
        continue

    #print(json.dumps(js, indent=4))

    time = js['rows'][0]['elements'][0]['duration']['value']
    print(time)
