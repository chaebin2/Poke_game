/* global switchBackground, loadMoney, loadMyPokemon */

document.addEventListener("DOMContentLoaded", () => {
  // 상점 섹션이 존재할 때만 동작
  if (document.getElementById("shop-section")) {
    initShop();
  }
});

async function initShop() {
  switchBackground("shop");
  try {
    const res = await fetch("http://localhost:8000/shop");
    const data = await res.json();
    renderShop(data.shop);
  } catch (err) {
    console.error("[shop] /shop API 실패", err);
  }
}

function renderShop(list) {
  const node = document.getElementById("shop-list");
  node.innerHTML = "";
  list.forEach((p) => {
    const card = document.createElement("div");
    card.className = "shop-card";
    card.innerHTML = `
      <img src="${p.image_url}" alt="${p.name}">
      <h3>${p.name}</h3>
      <p>${p.price} G</p>
      <button data-id="${p.id}">구매</button>
    `;
    card.querySelector("button").onclick = () => buyPokemon(p.id);
    node.appendChild(card);
  });
}

async function buyPokemon(id) {
  try {
    const res = await fetch(`http://localhost:8000/buy/${id}`);
    const data = await res.json();
    if (data.success === false) {
      alert(data.error || "구매 실패");
      return;
    }
    alert("구매 완료!");
    await loadMoney();
    await loadMyPokemon();       // 플레이어 섹션 즉시 갱신
  } catch (err) {
    console.error("[shop] /buy 실패", err);
  }
}
