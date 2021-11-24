const express = require("express"),
    cookieSession = require('cookie-session'),
    cookieParser = require('cookie-parser'),
    cors = require('cors'),
    bodyParser = require('body-parser'),
    app = express(),
    crypto = require('crypto'),
    SMTPController = require('./controllers/MailerController'),
    config = require('config');

var adminUsers = {}
app.use(cookieParser())
app.use(cors())
app.use(bodyParser.urlencoded({ extended: true }));
// app.use(express.json({ extended: false }))
app.use(bodyParser.json())

app.use('/static', express.static(__dirname + '/static'));

app.set("view engine", "ejs")
app.use(cookieSession({
    secret:"KeyCtF",
    name: 'session',
    keys: ['key1', 'key2', 'key3']
}))

app.get('/', (req, res)=>{
    console.log(req.query)
    if(req.cookies.secret != undefined){
        let cookies = req.cookies.secret.split("+&?35yh")[0]
        let role = Buffer.from(cookies, 'base64').toString()

        if(role.slice(-7) == "isAdmin"){
            if(role.slice(0,role.length-7) in config.get('adminUsers')){
                return res.render("index", {flag:config.get('flag')})
                
            }else{
                res.clearCookie("secret");
                res.render("login")
            }
        }else{
            console.log("user")
            return res.render("index", {flag: "Это привилегия администратора"})
        }
        
    }else{
        return res.render("login")
    }
    
      
})

app.post('/', (req, res)=>{
    console.log(req.body)
    let max
    let min
    if(parseInt(req.body.max) > parseInt(req.body.min)){
        max =  parseInt(req.body.max)
        min =  parseInt(req.body.min)
    }else{
        max =  parseInt(req.body.min)
        min =  parseInt(req.body.max)
    }
    let randomValue = isNaN(Math.floor(Math.random() * (max - min + 1)) + min) ? 0 : Math.floor(Math.random() * (max - min + 1)) + min
    console.log(randomValue)
    res.status(200).json({random:randomValue})
})

app.post('/login', (req, res) => {
    try{
        let result = "isUser"
        if(req.cookies.secret != undefined){
            let cookies = req.cookies.secret.split("+&?35yh")
            let role = Buffer.from(cookies[0], 'base64').toString()
            console.log("1")
            if(role.slice(-7) == "isAdmin"){
                console.log(role.slice(0,role.length-7))
                let mailLink = `http://${req.get('host')}/verifyRoute/${role.slice(0,role.length-7)}?password=${cookies[1].split('route')[0]}`
                mailOptions={
                    from:"barsukov1512@mail.ru",
                    to : role.slice(0,role.length-7),
                    subject : "Пожалуйста, подтвердите ваш Email",
                    html : `Привет,<br> Для завершения регистрации вам необходимо.<br><a href=${mailLink}>Подтвердить ваш Email</a>`
                }
                console.log(mailOptions);
                const mailer = SMTPController.sendMail(mailOptions)
                console.log(mailer)
                return res.status(200).json({result:true, message:`Администратор может находится в сети только с одного устройства, 
                подтвердите выход, перейдя по ссылке, отправленной на указанную вами почту и попробуйте войти снова`})
            }else{
                res.clearCookie("secret");
                return res.redirect('/')
            }
        }else{
            var password = crypto.createHash('md5').update(req.body.pass).digest('hex');
            if(req.body.email in config.get('adminUsers')){
                console.log(password, config.get('adminUsers')[req.body.email])
                if(config.get('adminUsers')[req.body.email] == password){
                    result = "isAdmin"
                }else{
                    return res.status(200).json({result:false, message: "Вы ввели неверный пароль"})
                }
            }
            let email = Buffer.from(`${req.body.email}${result}`);
            let base64email = email.toString('base64');

            let route = Buffer.from(`/login`);
            let base64route = route.toString('base64');

            let token = `${base64email}+&?35yh${password}route=${base64route}`
            res.cookie('secret', token)

            return res.status(200).json({result:true, redirect:true})
        } 
        
    }catch(err){
        console.log(err)
        return res.status(500).json({result:false})
    }
    
})

app.get("/verifyRoute/:email", (req,res) =>{
    config.get('adminUsers')[req.params.email] = req.query.password
    return res.redirect("/")
})

app.listen(config.get("PORT"), config.get("HOST"), ()=>{
    console.log("Server listening on port 3000")
})