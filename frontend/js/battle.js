/* global switchBackground */

document.addEventListener("DOMContentLoaded", () => {
  const btn = document.getElementById("battle-start-btn") || document.querySelector("#battle-section button");
  if (btn) btn.onclick = startBattle;
});

document.getElementById("main-screen").style.display = "none";
document.getElementById("battle-screen").style.display = "block";

// 기존 함수 유지 + 확장
async function startBattle() {
  switchBackground?.("battle");
  const area   = document.getElementById("battle-area");
  const logBox = document.getElementById("battle-log");
  if (area) area.classList.remove("hidden");
  logBox.innerText = "전투 중...";

  try {
    const res  = await fetch("http://localhost:8000/battle");
    const data = await res.json();
    renderBattleLog(data);      // ➜ 기존 함수(아래 수정)
  } catch (err) {
    console.error("[battle] /battle 실패", err);
    logBox.innerText = "전투 진행 중 오류 발생!";
  }
}

/* ----------  업데이트된 renderBattleLog ---------- */
function renderBattleLog(data) {
  updateBattleView(data);   // 새 함수: HP/이미지 표시

  const box = document.getElementById("battle-log");
  if (data.turns && Array.isArray(data.turns)) {
    // turns 배열이 올 때 => 누적 로그
    data.turns.forEach((t) => box.innerText
