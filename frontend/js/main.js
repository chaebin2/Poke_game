// 📄 frontend/js/main.js
let myPokemonCount = 0;

/* ---------- 처음: Start 버튼만 세팅 ---------- */
document.addEventListener("DOMContentLoaded", () => {
  document.getElementById("start-btn").onclick = initGame;
});

/* ---------- 배경 전환 ---------- */
function switchBackground(type) {
  const body = document.body;
  body.classList.remove("default-background", "shop-background", "battle-background");
  body.classList.add(
    type === "shop"   ? "shop-background"   :
    type === "battle" ? "battle-background" : "default-background"
  );
}

async function initGame() {
  // 화면 전환
  document.getElementById("start-screen").classList.add("hidden");
  document.getElementById("main-screen").classList.remove("hidden");
  switchBackground("default");

  // 네비 버튼
  document.getElementById("nav-home-btn").onclick  = () => showSection("home");
  document.getElementById("nav-shop-btn").onclick  = () => showSection("shop");
  document.getElementById("nav-battle-btn").onclick = tryEnterBattle;

  /* 섹션 내부 '메인으로' 버튼 */
  document.getElementById("shop-to-main-btn").onclick =
  document.getElementById("battle-to-main-btn").onclick = () => showSection("home");

  // 첫 데이터
  await loadMoney();
  await loadShop();       // shop 리스트만 채움, 화면은 아직 숨김
  await loadMyPokemon();  // myPokemonCount 갱신 + 전투 버튼 활성/비활성
  showSection("shop");    // 메인 진입 시 상점 탭
}


/* ---------- 섹션 토글 ---------- */
function showSection(name){
  const shop   = document.getElementById("shop-section");
  const battle = document.getElementById("battle-section");

  if(name==="shop"){      shop.classList.remove("hidden");  battle.classList.add("hidden");  switchBackground("shop"); }
  else if(name==="battle"){ shop.classList.add("hidden");   battle.classList.remove("hidden"); switchBackground("battle"); }
  else{ /* home */        shop.classList.add("hidden");    battle.classList.add("hidden");   switchBackground("default"); }

  /* 전투가 끝나면 ‘메인으로’ 버튼 보이기 위해 상태 초기화 */
  if(name!=="battle"){
    document.getElementById("battle-to-main-btn").classList.add("hidden");
    document.getElementById("battle-start-btn").disabled = false;
  }
}

/* ---------- 전투 버튼 진입 검사 ---------- */
function tryEnterBattle(){
  if(myPokemonCount < 1){
    alert("상점에서 포켓몬을 구입하십시오.");
    showSection("shop");
    return;
  }
  showSection("battle");
}

/* ---------- loadMoney / loadShop (배경만) ---------- */
async function loadMoney(){
  const res = await fetch("http://localhost:8000/money");
  document.getElementById("money-amount").innerText = `${(await res.json()).money}G`;
}

async function loadShop(){
  const res   = await fetch("http://localhost:8000/shop");
  renderShop((await res.json()).shop);
}

/* ---------- 포켓몬 로드: 보유 수 반영 & 전투 버튼 제어 ---------- */
async function loadMyPokemon(){
  const res   = await fetch("http://localhost:8000/mypokemon");
  const list  = (await res.json()).pokemon || [];
  myPokemonCount = list.length;
  document.getElementById("nav-battle-btn").disabled = myPokemonCount < 1;
  renderMyPokemon(list);
}

/* --- renderShop / renderMyPokemon / selectPokemon / battle 관련 기존 함수는 그대로 --- */
