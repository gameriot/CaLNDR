
from __future__ import print_function
import httplib2
import os
import re

from apiclient import discovery
from oauth2client import client
from oauth2client import tools
from oauth2client.file import Storage

import datetime

try:
    import argparse
    flags = argparse.ArgumentParser(parents=[tools.argparser]).parse_args()
except ImportError:
    flags = None

# If modifying these scopes, delete your previously saved credentials
# at ~/.credentials/calendar-python-quickstart.json
SCOPES = 'https://www.googleapis.com/auth/calendar.readonly'
CLIENT_SECRET_FILE = 'client_secret.json'
APPLICATION_NAME = 'Google Calendar API Python Quickstart'


def get_credentials():
    """Gets valid user credentials from storage.

    If nothing has been stored, or if the stored credentials are invalid,
    the OAuth2 flow is completed to obtain the new credentials.

    Returns:
        Credentials, the obtained credential.
    """
    home_dir = os.path.expanduser('~')
    credential_dir = os.path.join(home_dir, '.credentials')
    if not os.path.exists(credential_dir):
        os.makedirs(credential_dir)
    credential_path = os.path.join(credential_dir,
                                   'calendar-python-quickstart.json')

    store = Storage(credential_path)
    credentials = store.get()
    if not credentials or credentials.invalid:
        flow = client.flow_from_clientsecrets(CLIENT_SECRET_FILE, SCOPES)
        flow.user_agent = APPLICATION_NAME
        if flags:
            credentials = tools.run_flow(flow, store, flags)
        else: # Needed only for compatibility with Python 2.6
            credentials = tools.run(flow, store)
        print('Storing credentials to ' + credential_path)
    return credentials



def main():
    """Shows basic usage of the Google Calendar API.

    Creates a Google Calendar API service object and outputs a list of the next
    10 events on the user's calendar.
    """
    credentials = get_credentials()
    http = credentials.authorize(httplib2.Http())
    service = discovery.build('calendar', 'v3', http=http)

    now = datetime.datetime.utcnow().isoformat() + 'Z' # 'Z' indicates UTC time
    #print('Getting the upcoming 10 events')
    eventsResult = service.events().list(
        calendarId='primary', timeMin=now, maxResults=10, singleEvents=True,
        orderBy='startTime').execute()
    events = eventsResult.get('items', [])
    f = open("event.details.txt", 'w+')
    f.truncate()

    if not events:
        print('No upcoming events found.')
    for event in events:

        try:
            start = event['start'].get('dateTime').encode('utf-8')
            start_list = start.split("-")
            new_start = start_list[2].split("T")
            start_time = new_start[1].split(":")
            start_time_in_min = ((int(start_time[0])*60)+int(start_time[1]))
        except:
            start = None
        try:
            end = event['end'].get('dateTime').encode('utf-8')
            end_list = end.split("-")
            end_start = end_list[2].split("T")
            end_time = end_start[1].split(":")
            end_time_in_min = ((int(end_time[0])*60)+int(end_time[1]))
        except:
            end = None
        try:
            location = event['location'].encode('utf-8')
        except:
            location = None
        try:
            summary = event['summary'].encode('utf-8')
        except:
            summary = None
        event_details_list =[]
        event_details_list.append(start_list[1])
        event_details_list.append(new_start[0])
        event_details_list.append(start_time_in_min)
        event_details_list.append(end_time_in_min)
        event_details_list.append(location)
        event_details_list.append(summary)
        print(event_details_list)
        repr(event_details_list)
        f.write(repr(event_details_list))
    f.close()


if __name__ == '__main__':
    main()
