/***
    * EMQX's default port for ws connection is 8083 and for wss connection is 8084.
    * Note that you need to add a path after the connection address, such as /mqtt.
    */

const url = 'wss://broker.emqx.io:8084/mqtt'
const topic = 'board/balabolek'
const mqtt_options = {
  clean: true,
  connectTimeout: 4000,
  clientId: 'BALABOLEK-' + Math.floor(Math.random() * 16777215).toString(16),
  username: 'balabolek',
  password: 'balabolek',
}
