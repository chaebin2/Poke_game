/* global switchBackground */

document.addEventListener("DOMContentLoaded", () => {
  if (document.getElementById("player-section")) {
    loadMyPokemon();            // main.js �� �̹� ���ǵ� �����Ƿ� ���� ȣ��
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

  // �̹� localStorage �� ���õ� �ִ� ���ϸ��� ������ ǥ��
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

  // ���� ���(���õ� ���ϸ� ǥ��)
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
        <h3>���õ� ���ϸ�</h3>
        <img src="${target.image_url}" width="96">
        <p>${target.name} (Lv.${target.level})</p>
      `;
    });
}
