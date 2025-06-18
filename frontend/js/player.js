/* global switchBackground */

document.addEventListener("DOMContentLoaded", () => {
  if (document.getElementById("player-section")) {
    loadMyPokemon();            // main.js 에 이미 정의돼 있으므로 직접 호출
  }
});

function renderMyPokemon(list) {
  const container = document.getElementById("player-pokemon-list");
  container.innerHTML = "";
  list.forEach((p, idx) => {
    const div = document.createElement("div");
    div.className = "my-pokemon";
    div.innerHTML = `
      <span>${idx + 1}. ${p.name} (Lv.${p.level})</span>
      <img src="${p.image_url}" width="64">
    `;
    div.onclick = () => selectPokemon(p.id);
    container.appendChild(div);
  });

  // 이미 localStorage 에 선택돼 있던 포켓몬이 있으면 표시
  const sel = localStorage.getItem("selectedPokemonId");
  if (sel) highlightSelected(sel);
}

function selectPokemon(id) {
  localStorage.setItem("selectedPokemonId", id);
  highlightSelected(id);
}

function highlightSelected(id) {
  document.querySelectorAll(".my-pokemon").forEach((el) => {
    el.classList.toggle("selected", el.onclick.toString().includes(`(${id})`));
  });

  // 메인 상단(선택된 포켓몬 표시)
  fetch("http://localhost:8000/mypokemon")
    .then((r) => r.json())
    .then((d) => {
      const target = d.pokemon.find((p) => p.id === Number(id));
      if (!target) return;
      const box = document.getElementById("selected-pokemon") || (() => {
        const div = document.createElement("div");
        div.id = "selected-pokemon";
        document.body.prepend(div);
        return div;
      })();
      box.innerHTML = `
        <h3>선택된 포켓몬</h3>
        <img src="${target.image_url}" width="96">
        <p>${target.name} (Lv.${target.level})</p>
      `;
    });
}
