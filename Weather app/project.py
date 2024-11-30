import requests
import streamlit as st
from datetime import datetime, timedelta
from collections import Counter


def main():
    logo_url = "https://i.pinimg.com/originals/bd/68/0d/bd680d0d258c34c15475b6e2f4067118.png"
    st.set_page_config(
    page_title="Weather App",
    page_icon=logo_url,
    layout="centered",
    initial_sidebar_state="expanded"
    )

    API_key = 'add53657e88035d4ca3c555652530225'
    default_unit = 'metric'

    logo = st.columns(5)
    with logo[2]:
        st.image(logo_url, width=100, caption='Wather app')

    default_unit = st.sidebar.radio('Unit settigs', ["Metric", "Imperial"], 
                                    captions=["Celsius, Km/h", "Fahrenheit, mph"])
    city_name = st.text_input('', placeholder='Weather in your city') 


    # Get the current weather data
    url = f'https://api.openweathermap.org/data/2.5/weather?q={city_name}&appid={API_key}&units={default_unit}'
    data = requests.get(url).json()

    if data['cod'] == 200:
        # Assign the longitude and latitude of the city
        lon = data['coord']['lon']
        lat = data['coord']['lat']

        # Get the data for the next 5 days in the city
        url2 = f'https://api.openweathermap.org/data/2.5/forecast?lat={lat}&lon={lon}&appid={API_key}&units={default_unit}'
        data2 = requests.get(url2).json()

        # Assign the values of the next  5 days to 5 different lists
        today, next_day, next_day_2, next_day_3, next_day_4, next_day_5 = get_next_days_weather(data2, data)

        # Get the local hours
        local_hours = (datetime.fromtimestamp(data['dt']) + timedelta(seconds=data['timezone'])).strftime('%H:%M')

        # Get the current temperature data
        name, country, current_temp, description = get_current_weather(data)
        temperature_emoji = get_emoji(description, today, local_hours)

        # Print the current data
        col1, col2, col3, col4, col5 = st.columns(5)
        col3.metric('', temperature_emoji)
        col3.metric(f'{name}, {country}', f'{current_temp}º')
        col3.metric(f'{description}', '')

        st.divider()

        fcast = st.columns(5)
        # Append next day information if today list length is lower then 5
        prevision_next_12_hours = today
        if len(prevision_next_12_hours) == 1:
            for i in range(4):
                prevision_next_12_hours.append(next_day[i])
        elif len(prevision_next_12_hours) == 2:
            for i in range(3):
                prevision_next_12_hours.append(next_day[i])
        elif len(prevision_next_12_hours) == 3:
            for i in range(2):
                prevision_next_12_hours.append(next_day[i])
        elif len(prevision_next_12_hours) == 4:
            for i in range(1):
                prevision_next_12_hours.append(next_day[i])


        # Get all the values to the 3 hour forecast
        for i in range(len(prevision_next_12_hours)):
            # Break out of the loop if the list is bigger then 5
            if i > 4:
                break

            hour = prevision_next_12_hours[i]['hour']
            temp = prevision_next_12_hours[i]['temp_max']
            temp_emoji = get_emoji(prevision_next_12_hours[i]['description'], prevision_next_12_hours, hour)
          
            with fcast[i]:
                st.subheader(hour)
                st.header(temp_emoji)
                st.subheader(f"{round(temp)}º")

        st.divider()
        st.header('5 day forecast')
        st.text('')

        print_forecast_information(next_day, default_unit)
        print_forecast_information(next_day_2, default_unit)
        print_forecast_information(next_day_3, default_unit)
        print_forecast_information(next_day_4, default_unit)
        print_forecast_information(next_day_5, default_unit)


        # Get sunrise and sunset hours
        sun_rise = (datetime.fromtimestamp(data['sys']['sunrise']) + timedelta(seconds=data['timezone'])).strftime('%H:%M')
        sun_set = (datetime.fromtimestamp(data['sys']['sunset']) + timedelta(seconds=data['timezone'])).strftime('%H:%M')

        st.title('')

        rise_set, feels = st.columns(2, gap='medium')
        # Sunrise data
        rise_set = rise_set.container(border=True)
        rise_set.metric('🌅 Sunrise', '')
        rise_set.subheader(sun_rise)
        rise_set.metric(f'Sunset: {sun_set}', '')

        # Feels like data
        feel_like = round(data['main']['feels_like'])
        feels = feels.container(border=True)
        feels.metric('🌡️ Feels like', '')
        feels.subheader(f'{feel_like}º')
        feels.metric(f'Actual: {current_temp}º', '')
        
        # Wind data
        with st.container(border=True):
            wind1, wind2 = st.columns(2, gap='large')
            speed, degree = get_wind_info(data, default_unit)
            
            wind1.metric('Wind', '')
            wind1.subheader('Wind')
            wind1.subheader('Direction')
            
            # Invisible char
            wind2.text('\u200b')
            wind2.subheader(speed)
            wind2.subheader(degree)
            
        pres, hum = st.columns(2, gap='medium')
        # Pressure data
        pressure = data['main']['pressure']
        pres = pres.container(border=True)
        pres.metric('Pressure', '')
        pres.subheader(f'{pressure} hPa')
        
        # Humidity data
        humidity = data['main']['humidity']
        hum = hum.container(border=True)
        hum.metric('Humidity', '')
        hum.subheader(f'{humidity} %')



def get_wind_info(data, units):
    ''' Return speed and degrees of the current wind data '''
    speed = data['wind']['speed']
    degrees = data['wind']['deg']
    
    if units == 'Metric':
        speed = str(round(speed * 3.6)) + ' Km/h'
    else:
        speed = str(round(speed)) + ' mph'
    
    if 348.75 <= degrees or degrees < 11.25:
        degrees = str(degrees) + 'º N'
    elif 11.25 <= degrees < 78.75:
        degrees = str(degrees) + 'º NE'
    elif 78.75 <= degrees < 101.25:
        degrees = str(degrees) + 'º E'
    elif 101.25 <= degrees < 168.75:
        degrees = str(degrees) + 'º SE'
    elif 168.75 <= degrees < 191.25:
        degrees = str(degrees) + 'º S'
    elif 191.25 <= degrees < 258.75:
        degrees = str(degrees) + 'º SW'
    elif 258.75 <= degrees < 281.25:
        degrees = str(degrees) + 'º W'
    elif 281.25 <= degrees < 348.75:
        degrees = str(degrees) + 'º NW'

    return speed, degrees 
    

def print_forecast_information(list, unit):
        ''' Print the forecast information '''
        f = st.columns(4)

        # Get all the values needed
        maximum, minimum = max_and_min(list)
        day_week = day_of_week(list)
        emoji_forecast = get_emoji_forecast(list)

        # Add color to the min and max separator (-----)
        string = forecast_by_unit(unit, minimum, maximum)

        # Print in the website
        with f[0]:
            st.subheader(f'{day_week}')
        with f[1]:
            st.subheader(f'{emoji_forecast} ')
        with f[3]:
            st.subheader(f'{round(minimum)}º {string} {round(maximum)}º')


def forecast_by_unit(unit, min, max):
    ''' Return the color separator (-----) in either unit settings '''
    string = ''
    
    match unit:
        case 'Metric':
            if min <= 10:
                string += ':blue[--]'
            elif min < 20:
                string += ':green[--]'
            elif min < 25:
                string += ':orange[--]'
            else:
                string += ':red[--]'

            if max <= 10:
                string += ':blue[---]'
            elif max < 20:
                string += ':green[---]'
            elif max < 25:
                string += ':orange[---]'
            else:
                string += ':red[---]'
                
        case 'Imperial':
            if min <= 50:
                string += ':blue[--]'
            elif min < 68:
                string += ':green[--]'
            elif min < 77:
                string += ':orange[--]'
            else:
                string += ':red[--]'

            if max <= 50:
                string += ':blue[---]'
            elif max < 68:
                string += ':green[---]'
            elif max < 77:
                string += ':orange[---]'
            else:
                string += ':red[---]'
                
    return string   

def get_emoji_forecast(list):
        ''' Get the most common description in the forecast and return the corresponding emoji '''
        emojis = []
        for i in range(len(list)):
            emojis.append(list[i]['description'])

        emojis = Counter(emojis)

        # hour = '12' to return a sunny emoji
        return get_emoji(max(emojis, key=emojis.get), list, '12')


def get_sun_rise_and_set(list):
    return list[0]['sunrise'], list[0]['sunset']

def get_emoji(description, list, hour):
    ''' Check if it is day time or night time and return the corresponding emoji'''

    s = ''
    rise, set = get_sun_rise_and_set(list)

    if rise < hour < set:
        match description:
            case 'clear sky':
                s = '☀️'
            case 'few clouds':
                s = '🌤️'
            case 'overcast clouds' | 'scattered clouds' | 'broken clouds':
                s = '☁️'
            case 'shower rain' | 'heavy intensity rain':
                s = '🌧️'
            case 'rain' | 'moderate rain' | 'light rain':
                s = '🌦️'
            case 'snow':
                s = '🌨️'
            case 'thunderstorm':
                s = '🌩️'
            case _:
                s = '🌧️'
    else:
        match description:
            case 'clear sky':
                s = '🌑'
            case 'overcast clouds' | 'scattered clouds' | 'broken clouds' | 'few clouds':
                s = '☁️'
            case 'rain' | 'moderate rain' | 'light rain' | 'shower rain':
                s = '🌧️'
            case 'snow':
                s = '🌨️'
            case 'thunderstorm':
                s = '🌩️'
            case _:
                s = '🌧️'

    return s



def get_current_weather(data):
    return data['name'], data['sys']['country'], round(data["main"]["temp"]), data["weather"][0]["description"]

def day_of_week(list):
    ''' Return an abreviation of the week day "Fri, Sat, etc" '''
    return list[0]['data'].strftime('%a') +'.'

def max_and_min(list):
    ''' Return the maximum and minimum value of temperature on that day '''
    return max(list, key=lambda x: x['temp_max'])['temp_max'], min(list, key=lambda x: x['temp_max'])['temp_max']


def get_next_days_weather(data2, data):
    # Get the current values of the temperature
    hour = (datetime.fromtimestamp(data['dt']) + timedelta(seconds=data['timezone'])).strftime('%H:%M')
    sunrise = (datetime.fromtimestamp(data2['city']['sunrise']) + timedelta(seconds=data['timezone'])).strftime('%H:%M')
    sunset = (datetime.fromtimestamp(data2['city']['sunset']) + timedelta(seconds=data['timezone'])).strftime('%H:%M')

    # Array to insert data for next 5 days
    # Set a default value for the list today
    today = [{'hour': hour, 'temp_max' : data['main']['temp_max'], 'sunrise': sunrise, 'sunset': sunset,
               'description': data['weather'][0]['description']}]
    tomorrow = []
    data_second = []
    data_third = []
    data_fourth = []
    data_fifth = []

    # Get next 5 days
    today_day = datetime.now().date()
    tomorrow_day = today_day + timedelta(days=1)
    sec_day = today_day+ timedelta(days=2)
    third_day = today_day + timedelta(days=3)
    fourth_day = today_day + timedelta(days=4)
    fifth_day = today_day + timedelta(days=5)

    for o in data2['list']:
        # Convert timestamp to an datetime object
        api_date = datetime.fromtimestamp(o['dt']).date()
        sunrise = (datetime.fromtimestamp(data2['city']['sunrise']) + timedelta(seconds=data['timezone'])).strftime('%H:%M')
        sunset = (datetime.fromtimestamp(data2['city']['sunset']) + timedelta(seconds=data['timezone'])).strftime('%H:%M')
        hours = (datetime.fromtimestamp(o['dt']) + timedelta(seconds=data['timezone'])).strftime('%H')

        # Compare the api_date with the current dict date
        if api_date == today_day:
            today.append({'hour': hours, 'temp_max': o['main']['temp_max'], 'description': o['weather'][0]['description']})

        elif api_date == tomorrow_day:
            tomorrow.append({'hour': hours, 'data': tomorrow_day, 'temp_max': o['main']['temp_max'], 'sunrise': sunrise, 'sunset': sunset,
                             'description': o['weather'][0]['description']})

        elif api_date == sec_day:
            data_second.append({'data': sec_day, 'temp_max': o['main']['temp_max'], 'sunrise': sunrise, 'sunset': sunset,
                                'description': o['weather'][0]['description']})

        elif api_date == third_day:
            data_third.append({'data': third_day, 'temp_max': o['main']['temp_max'], 'sunrise': sunrise, 'sunset': sunset,
                                'description': o['weather'][0]['description']})

        elif api_date == fourth_day:
            data_fourth.append({'data': fourth_day, 'temp_max': o['main']['temp_max'], 'sunrise': sunrise, 'sunset': sunset,
                                'description': o['weather'][0]['description']})

        elif api_date == fifth_day:
            data_fifth.append({'data': fifth_day, 'temp_max': o['main']['temp_max'], 'sunrise': sunrise, 'sunset': sunset,
                                'description': o['weather'][0]['description']})



    return today, tomorrow, data_second, data_third, data_fourth, data_fifth




if __name__ == '__main__':
    main()
