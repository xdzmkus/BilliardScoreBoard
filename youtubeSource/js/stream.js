
function getCommonMatchInfo(splitedValues) {
  return{
    player1Name: splitedValues[0],
    player2Name: splitedValues[1],

    player1Break: splitedValues[4],

    player1MatchPoint: splitedValues[12],
    player2MatchPoint: splitedValues[13],

    matchTotalFrames: splitedValues[14],

    player1FramePoint: splitedValues[15],
    player2FramePoint: splitedValues[16],

    player1Hadicap: splitedValues[17],
    player2Hadicap: splitedValues[18],
  }
}

const client  = mqtt.connect(url, mqtt_options)

client.on('connect', function () {
  console.log('Connected')
  // Subscribe to a topic
  client.subscribe(topic, function (err) {
    if (err) {
        console.log(err)
    }
  })
})

// Receive messages
client.on('message', function (topic, message)
{
  console.log(message.toString());

  var splitedValues = message.toString().split('~');
  var commonMatchInfo = getCommonMatchInfo(splitedValues);

  // fill players name and handicap
  if(commonMatchInfo.player1Hadicap == '0' && commonMatchInfo.player2Hadicap == '0')
  {
    document.getElementById('ply1-name').innerHTML = commonMatchInfo.player1Name;
    document.getElementById('ply2-name').innerHTML = commonMatchInfo.player2Name;
  }
  else
  {
    document.getElementById('ply1-name').innerHTML = commonMatchInfo.player1Name + " (" + commonMatchInfo.player1Hadicap + ")";
    document.getElementById('ply2-name').innerHTML = "(" + commonMatchInfo.player2Hadicap + ") " + commonMatchInfo.player2Name;
  }

  // fill match scores
  document.getElementById('ply1-match-score').innerHTML = commonMatchInfo.player1MatchPoint;
  document.getElementById('ply2-match-score').innerHTML = commonMatchInfo.player2MatchPoint;

  // fill race to value
  if(commonMatchInfo.matchTotalFrames == '0')
  {
    document.getElementById('total-score').innerHTML = "-";
  }
  else
  {
    document.getElementById('total-score').innerHTML = '(' + commonMatchInfo.matchTotalFrames + ')';
  }

  // fill frame scores
  if(commonMatchInfo.player1FramePoint == '0' && commonMatchInfo.player2FramePoint == '0')
  {
    document.getElementById('ply1-frame-score').innerHTML = "";
    document.getElementById('ply2-frame-score').innerHTML = "";
  }
  else
  {
    document.getElementById('ply1-frame-score').innerHTML = commonMatchInfo.player1FramePoint;
    document.getElementById('ply2-frame-score').innerHTML = commonMatchInfo.player2FramePoint;
  }

  // show who is starting frame
  if (commonMatchInfo.player1Break == 1)
  {
    document.getElementById('ply1-break').style.visibility = "visible";
    document.getElementById('ply2-break').style.visibility = "hidden";
  }
  else
  {
    document.getElementById('ply1-break').style.visibility = "hidden";
    document.getElementById('ply2-break').style.visibility = "visible";
  }
})
