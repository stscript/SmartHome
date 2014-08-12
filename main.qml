import QtQuick 2.2
import QtQuick.Window 2.1
import QtQuick.Controls 1.2
import HttpControl 1.0
Window {
    visible: true
    width: 1024
    height: 600

    Image {
        id: bg
        source: "./image/background.png"
    }
    Image {
        id: room1
        source: "./image/room1.png"
    }
    Image {
        id: room2
        source: "./image/room2.png"
    }
    Image {
        id: room3
        source: "./image/room3.png"
    }
    Image {
        id: room4
        source: "./image/room4.png"
    }
    Image {
        id: room5
        source: "./image/room5.png"
    }
    Image {
        id: room6
        source: "./image/room6.png"
    }
    HttpCTL{
        id:hctl
        onAirHaveChange:{
            console.log('a')
            if(this.airPower == "1")
            {
                airtemp.visible = true;
                airmode.visible = true;
                airt1.visible = true;
                airt2.visible = true;
                airtemp.text = this.airTemp;
                if(this.airMode == "1")
                {
                    airmode.text = "制冷";
                }else if(this.airMode == "2")
                {
                    airmode.text = "除湿";
                }else if(this.airMode == "3")
                {
                    airmode.text = "铺热";
                }else if(this.airMode == "4")
                {
                    airmode.text = "睡眠";
                }

           //     airmode.text = this.airMode;
                console.log(this.airTemp)
            }else {
                airtemp.visible = false;
                airmode.visible = false;
                airt1.visible = false;
                airt2.visible = false;
            }
        }
        onLightHaveChange: {
            console.log('b');
            this.light1?r1.color = "#00ff00":r1.color = "#ff0000";
            this.light1?room1.source = "":room1.source = "./image/room1.png";

            this.light2?r2.color = "#00ff00":r2.color = "#ff0000";
            this.light2?room2.source = "":room2.source = "./image/room2.png";

            this.light3?r3.color = "#00ff00":r3.color = "#ff0000";
            this.light3?room3.source = "":room3.source = "./image/room3.png";

            this.light4?r4.color = "#00ff00":r4.color = "#ff0000";
            this.light4?room4.source = "":room4.source = "./image/room4.png";

            this.light5?r5.color = "#00ff00":r5.color = "#ff0000";
            this.light5?room5.source = "":room5.source = "./image/room5.png";

            this.light6?r6.color = "#00ff00":r6.color = "#ff0000";
            this.light6?room6.source = "":room6.source = "./image/room6.png";
        }
        onTvHaveChange:{
            console.log('b');
            if(this.tvPower == true)
            {
                tvvoice.visible = true;
                tvchangle.visible = true;
                tvt1.visible = true;
                tvt2.visible = true;
                tvvoice.text = this.tvVoice;
                tvchangle.text = this.tvChangle;
            }else{
                tvvoice.visible = false;
                tvchangle.visible = false;
                tvt1.visible = false;
                tvt2.visible = false;
            }
        }
    }

    Rectangle{
        id:r3
        width:20
        height: 20
        color:"#ff0000"
        radius: 10
        x:403
        y:195
        MouseArea {
            anchors.fill: parent
            onClicked: {
                hctl.light3?hctl.light3 = false:hctl.light3 = true;
                hctl.dataGoLight();
            }
        }
    }
    Rectangle{
        id:r2
        width:20
        height: 20
        radius: 10
        color:"#ff0000"
        x:535
        y:223
        MouseArea {
            anchors.fill: parent
            onClicked: {
                hctl.light2?hctl.light2 = false:hctl.light2 = true;
                hctl.dataGoLight();
            }
        }
    }
    Rectangle{
        id:r4
        width:20
        height: 20
        radius: 10
        color:"#ff0000"
        x:350
        y:230
        MouseArea {
            anchors.fill: parent
            onClicked: {
                hctl.light4?hctl.light4 = false:hctl.light4 = true;
                hctl.dataGoLight();
            }
        }
    }
    Rectangle{
        id:r5
        width:20
        height: 20
        radius: 10
        x:405
        y:330
        color:"#ff0000"
        MouseArea {
            anchors.fill: parent
            onClicked: {
                hctl.light5?hctl.light5 = false:hctl.light5 = true;
                hctl.dataGoLight();
            }
        }
    }
    Rectangle{
        id:r6
        width:20
        height: 20
        radius: 10
        x:525
        y:380
        color:"#ff0000"
        MouseArea {
            anchors.fill: parent
            onClicked: {
                hctl.light6?hctl.light6 = false:hctl.light6 = true;
                hctl.dataGoLight();
         }
        }
    }
    Rectangle{
        id:r1
        width:20
        height: 20
        radius: 10
        x:670
        y:312
        color:"#ff0000"
        MouseArea {
            anchors.fill: parent
            onClicked: {
                hctl.light1?hctl.light1 = false:hctl.light1 = true;
                hctl.dataGoLight();
            }
        }
    }
    Button{
        id:airOpenClose
        x:60
        y:320
        text: "开关"
        onClicked: {

           hctl.airPower=="1"?hctl.airPower="0":hctl.airPower="1";
           hctl.dataGoAir();
        }
    }
    Button{
        id:airMode
        x:180
        y:320
        text: "模式切换"
        onClicked: {
            if(hctl.airMode==="1"){
                hctl.airMode = "2";

            }else if(hctl.airMode==="2"){
                hctl.airMode = "3";
            }else if(hctl.airMode==="3"){
                hctl.airMode = "4";
            }else if(hctl.airMode==="4"){
                hctl.airMode = "1";
            }
            hctl.dataGoAir();
        }
    }
    Button{
        id:airUp
        x:60
        y:380
        text: "温度增"
        onClicked: {
            var i = parseInt(hctl.airTemp);
            if(i<31)
                i++;
            hctl.airTemp=i.toString();
            hctl.dataGoAir();
        }

    }
    Button{
        id:airDown
        x:180
        y:380
        text: "温度减"
        onClicked: {
            var i = parseInt(hctl.airTemp);
            if(i>16)
                i--;
            hctl.airTemp=i.toString();
            hctl.dataGoAir();

        }
    }

    Button{
        id:tvOpenClose
        x:785
        y:320
        text: "开关"

        onClicked: {
            hctl.tvPower?hctl.tvPower = false:hctl.tvPower = true;
            hctl.dataGoTv();

        }
    }
    Button{
        id:tvVoiceClean
        x:915
        y:320
        text: "静音"
        onClicked: {
            hctl.tvVoice = 0;
            hctl.dataGoTv();
        }
    }
    Button{
        id:tvModeUp
        x:785
        y:360
        text: "频道增"
        onClicked: {
            if(hctl.tvChangle<9)
                hctl.tvChangle ++;
            else
                hctl.tvChangle = 0;
            hctl.dataGoTv();
        }
    }
    Button{
        id:tvVoiceUp
        x:785
        y:400
        text: "音量增"
        onClicked: {
            hctl.tvVoice<30?hctl.tvVoice++:hctl.tvVoice = 30;
            hctl.dataGoTv();
        }
    }
    Button{
        id:tvModeDown
        x:915
        y:360
        text: "频道减"
        onClicked: {
            hctl.tvChangle>0?hctl.tvChangle--:hctl.tvChangle = 9;
            hctl.dataGoTv();
        }
    }
    Button{
        id:tvVoiceDown
        x:915
        y:400
        text: "音量减"
        onClicked: {
            hctl.tvVoice>0?hctl.tvVoice--:hctl.tvVoice = 0;
            hctl.dataGoTv();

        }
    }
    Text {
        x:70
        y:200
        id:airt1
        font.pointSize: 15
        visible: false
        text: qsTr("当前温度(度)：")
    }
    Text {
        x:70
        y:250
        id:airt2
        visible: false
        font.pointSize: 15
        text: qsTr("当前模式：")
    }
    Text {
        id:airtemp
        x:210
        y:200
        visible: false
        font.pointSize: 12
        text:qsTr("25")
    }
    Text {
        id:airmode
        x:200
        y:250
        visible: false
        font.pointSize: 12
        text:qsTr("制冷")
    }
    Text{
        id:tvt1
        x:800
        y:180
        visible: false
        font.pointSize: 15
        text:qsTr("频道：")
    }
    Text{
        id:tvt2
        x:800
        y:230
        visible: false
        font.pointSize: 15
        text:qsTr("音量：")
    }

    Text {
        id: tvvoice
        y:230
        x:880
        visible: false
        font.pointSize: 14
        text: qsTr("0")
    }
    Text {
        id: tvchangle
        x:880
        y:180
        visible: false
        font.pointSize: 14
        text: qsTr("0")
    }
}
