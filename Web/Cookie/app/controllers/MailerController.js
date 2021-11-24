const nodemailer = require("nodemailer"),
    smtpTransport = nodemailer.createTransport({
        host: "smtp.mail.ru",
        port: 465,
        secure: true, // true for 465, false for other ports
        auth: {
          user: "barsukov1512@mail.ru", // generated ethereal user
          pass: "U)i2V1iaauOT" // generated ethereal password
        }
    });

let SMTPController = {
    sendMail: (req) =>{
        smtpTransport.sendMail(req, function(error, response){
            if(error){
                console.log(error);
                return false;
            }else{
                console.log("Message sent: " + response.message);
                return true;
            }
        });
    }
}

module.exports = SMTPController