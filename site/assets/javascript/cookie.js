export function getCurrendSlide(){
    let cookie = getCookie("currendSlide")
    if (cookie == ""){
        return 0
    }
    return Number(cookie)

}
export function setCurrendSlide(value){
    setCookie("currendSlide", value,  24 * 60 *60 *1000)
}






export function setCookie(cname, cvalue, extraTime) {
    const d = new Date();
    d.setTime(d.getTime() + extraTime);
    let expires = "expires="+d.toUTCString();
    document.cookie = cname + "=" + cvalue + ";" + expires + ";path=/";
  }
  
export function getCookie(cname) {
    let name = cname + "=";
    let ca = document.cookie.split(';');
    for(let i = 0; i < ca.length; i++) {
      let c = ca[i];
      while (c.charAt(0) == ' ') {
        c = c.substring(1);
      }
      if (c.indexOf(name) == 0) {
        return c.substring(name.length, c.length);
      }
    }
    return "";
  }
