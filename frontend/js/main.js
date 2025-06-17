// 📄 frontend/js/main.js

document.addEventListener("DOMContentLoaded", async () => {
  switchBackground("default");
  await loadMoney();
  await loadShop();
  await loadMyPokemon();
});

function switchBackground(type) {
  const body = document.body;
  body.classList.remove("default-background", "shop-background", "battle-background");

  switch (type) {
    case "shop":
      body.classList.add("shop-background");
      break;
    case "battle":
      body.classList.add("battle-background");
      break;
    default:
      body.classList.add("default-background");
  }
}

async function loadMoney() {
  try {
    const res = await fetch("http://localhost:8000/money");
    const data = await res.json();
    document.getElementById("money-amount").innerText = `${data.money}G`;
  } catch (err) {
    console.error("/money 연동 오류", err);
  }
}

async function loadShop() {
  try {
    switchBackground("shop");
    const res = await fetch("http://localhost:8000/shop");
    const data = await res.json();
    renderShop(data.shop);
  } catch (err) {
    console.error("/shop 연동 오류", err);
  }
}

function renderShop(shopList) {
  const shopContainer = document.getElementById("shop-list");
  shopContainer.innerHTML = "";
  shopList.forEach((pokemon) => {
    const card = document.createElement("div");
    card.className = "shop-card";
    card.innerHTML = `
      <img src="${pokemon.image_url}" alt="${pokemon.name}" />
      <h3>${pokemon.name}</h3>
      <p>가격: ${pokemon.price}G</p>
      <button onclick="buyPokemon(${pokemon.id})">구매</button>
    `;
    shopContainer.appendChild(card);
  });
}

async function buyPokemon(id) {
  try {
    const res = await fetch(`http://localhost:8000/buy/${id}`);
    const data = await res.json();
    alert("구매 완료!");
    await loadMoney();
    await loadMyPokemon();
  } catch (err) {
    console.error("/buy/{id} 연동 오류", err);
  }
}

async function loadMyPokemon() {
  try {
    const res = await fetch("http://localhost:8000/mypokemon");
    const data = await res.json();
    renderMyPokemon(data.pokemon);
  } catch (err) {
    console.error("/mypokemon 연동 오류", err);
  }
}

function renderMyPokemon(list) {
  const container = document.getElementById("player-pokemon-list");
  container.innerHTML = "";
  list.forEach((p, idx) => {
    const div = document.createElement("div");
    div.className = "my-pokemon";
    div.innerText = `${idx + 1}. ${p.name} (Lv.${p.level})`;
    div.onclick = () => selectPokemon(p.id);
    container.appendChild(div);
  });
}

function selectPokemon(id) {
  localStorage.setItem("selectedPokemonId", id);
  alert(`포켓몬 ${id}번 선택됨!`);
  renderSelectedPokemon(id);  // 선택된 포켓몬 표시 함수 호출
}

async function renderSelectedPokemon(id) {
  try {
    const res = await fetch("http://localhost:8000/mypokemon");
    const data = await res.json();
    const selected = data.pokemon.find(p => p.id === id);
    const container = document.getElementById("selected-pokemon");
    if (selected) {
      container.innerHTML = `
        <img src="${selected.image_url}" alt="${selected.name}" />
        <p>${selected.name} (Lv.${selected.level})</p>
      `;
    }
  } catch (err) {
    console.error("선택된 포켓몬 렌더링 오류", err);
  }
}

async function startBattle() {
  try {
    switchBackground("battle");
    const res = await fetch("http://localhost:8000/battle");
    const data = await res.json();
    renderBattleLog(data);
  } catch (err) {
    console.error("/battle 연동 오류", err);
  }
}

function renderBattleLog(logData) {
  const log = document.getElementById("battle-log");
  log.innerText = logData.output || JSON.stringify(logData);
}
