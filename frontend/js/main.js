/* ───── 화면 전환 ───── */
function openMain(){
  setScreen("main");
}
function openShop(){
  setScreen("shop");
  loadShop();          // API /shop
}
function openBattle(){
  // 포켓몬이 0마리면 경고 후 메인으로
  fetch("/mypokemon")
    .then(r=>r.json()).then(list=>{
      if(!list.mypokemon || list.mypokemon.length===0){
        alert("포켓몬이 없습니다! 상점에서 먼저 구입하세요.");
        openShop(); return;
      }
      setScreen("battle");
      startBattle();
    });
}

function setScreen(target){
  document.body.className = {
    main:"default-background",
    shop:"shop-background",
    battle:"battle-background"
  }[target];

  ["main","shop","battle"].forEach(id=>{
    document.getElementById(id+"-screen").classList.toggle(
      "hidden", id!==target
    );
  });
}

/* ───── 상점 로드 & 구매 ───── */
function loadShop(){
  fetch("/shop").then(r=>r.json()).then(data=>{
    const box = document.getElementById("shop-list");
    box.innerHTML = data.shop.map(p=>`
      <div class="card">
        <img src="${p.image_url}" width="120"><br>
        ${p.name}<br>
        1000 G<br>
        <button onclick="buy(${p.id})">구매</button>
      </div>`).join("");
  });
}
function buy(id){
  fetch("/buy/"+id).then(r=>r.json()).then(js=>{
    if(js.success){ alert(`${js.pokemon.name} 구입!`); }
  });
}

/* ───── 전투 로직 (로그·버튼 토글) ───── */
function startBattle(){
  const log = document.getElementById("battle-log");
  const atkBtn = document.getElementById("attack-btn");
  const backBtn = document.getElementById("battle-back-btn");
  log.textContent = "전투 시작…";
  atkBtn.disabled = false;
  backBtn.classList.add("hidden");
}

function attackTurn(){
  fetch("/battle").then(r=>r.json()).then(lines=>{
    const log = document.getElementById("battle-log");
    if(lines.result==="no_pokemon"){
      alert("포켓몬이 없습니다!"); openShop(); return;
    }
    // lines 는 배열일 수도, 마지막 result 하나일 수도 있음
    log.innerHTML = Array.isArray(lines)? lines.map(l=>JSON.stringify(l)).join("<br>")
                                         : JSON.stringify(lines);

    if(lines.result){          // 승패가 결정된 순간
      document.getElementById("attack-btn").disabled = true;
      document.getElementById("battle-back-btn").classList.remove("hidden");
    }
  });
}
