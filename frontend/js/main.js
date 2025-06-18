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

/* ---------- 게임 시작 후 ---------- */
async function initGame() {
  // 화면 전환
  document.getElementById("start-screen").classList.add("hidden");
  document.getElementById("main-screen").classList.remove("hidden");
  switchBackground("default");

  // 네비 버튼
  document.getElementById("nav-shop-btn").onclick   = () => showSection("shop");
  document.getElementById("nav-battle-btn").onclick = tryEnterBattle;

  // 첫 데이터 로드
  await loadMoney();
  await loadShop();        // 배경만 변경, 섹션은 아직 숨김
  await loadMyPokemon();   // 보유 수 세팅 & 전투 버튼 활성/비활성
  showSection("shop");     // 메인 진입 시 상점 화면
}

/* ---------- 섹션 토글 ---------- */
function showSection(name){
  ["shop","battle"].forEach(id=>{
    document.getElementById(id+"-section").classList.toggle("hidden", id!==name);
  });
  if(name==="shop")   switchBackground("shop");
  if(name==="battle") switchBackground("battle");
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
