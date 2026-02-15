#!/usr/bin/env bash
set -euo pipefail

USERN="${SUDO_USER:-$(whoami)}"
HOME_DIR="$(getent passwd "$USERN" | cut -d: -f6)"
if [[ -z "$HOME_DIR" || ! -d "$HOME_DIR" ]]; then
  echo "Δεν βρέθηκε home directory για τον χρήστη '$USERN'." >&2
  exit 1
fi

# ΔΕΝ χρησιμοποιούμε πλέον /tmp αλλά έναν κατάλογο μέσα στο HOME
TMP_DIR="${HOME_DIR}/backup-tmp"
mkdir -p "${TMP_DIR}"

#TMP_DIR="/tmp"
ETC_DIR="${TMP_DIR}/${USERN}-etc"
HOME_TAR="${TMP_DIR}/${USERN}-home.tar.gz"
ETC_TAR="${TMP_DIR}/${USERN}-etc.tar"
FINAL_TAR_GZ="${HOME_DIR}/${USERN}-all.tar.gz"

echo "=== Σενάριο backup για χρήστη: ${USERN} ==="
echo

# --- 1. sudo password ---
echo "Θα ζητηθεί sudo password (αν χρειάζεται)..."
if ! sudo -v; then
  echo "Δεν δόθηκε σωστό sudo password ή δεν υπάρχει sudo. Έξοδος." >&2
  exit 1
fi
sudo sh -c 'echo >/dev/null'

# --- 2. Ζήτηση καταλόγου φοιτητή ---
read -rp $'Δώσε τη διαδρομή του καταλόγου που δημιούργησες στο βήμα "Οδηγίες": ' STUDENT_DIR_INPUT
if [[ -z "${STUDENT_DIR_INPUT// }" ]]; then
  echo "Δεν δόθηκε έγκυρη διαδρομή. Έξοδος." >&2
  exit 1
fi
if [[ "${STUDENT_DIR_INPUT}" = /* ]]; then
  STUDENT_DIR="${STUDENT_DIR_INPUT}"
else
  STUDENT_DIR="$(pwd)/${STUDENT_DIR_INPUT}"
fi
if [[ ! -d "${STUDENT_DIR}" ]]; then
  echo "Ο κατάλογος '${STUDENT_DIR}' δεν υπάρχει. Έξοδος." >&2
  exit 1
fi

# --- 3. Δημιουργία tar.gz με τον κατάλογο και τα dotfiles ---
echo
echo "Δημιουργία tar.gz με τον κατάλογο του φοιτητή και όλα τα dotfiles του home..."
cd /
# Φτιάχνουμε λίστα dotfiles/φακέλων στο home
#DOTFILES=()
##while IFS= read -r d; do DOTFILES+=("home/${USERN}/${d}"); done < <(find "$HOME_DIR" -maxdepth 1 -mindepth 1 -name ".*" -printf "%P\n")
##sudo tar -czf "$HOME_TAR" "${STUDENT_DIR#/}" "${DOTFILES[@]}"
#
#while IFS= read -r d; do
#  DOTFILES+=("home/${USERN}/${d}")
#done < <(find "$HOME_DIR" -maxdepth 1 -mindepth 1 -name ".*" -printf "%P\n")

# Φτιάχνουμε λίστα ΜΟΝΟ με τα βασικά bash dotfiles
DOTFILES=()
BASH_DOTFILES=(.bashrc .bash_profile .bash_logout .bash_history .profile .inputrc)
for f in "${BASH_DOTFILES[@]}"; do
  if [[ -e "${HOME_DIR}/${f}" ]]; then
    DOTFILES+=("${HOME_DIR}/${f}")
  fi
done





# ΕΔΩ η διαφορά: γράφουμε το tar μέσα στο $HOME (backup-tmp), όχι στο /tmp
sudo tar -czf - "${STUDENT_DIR#/}" "${DOTFILES[@]}" > "$HOME_TAR"

sudo chown "$USERN":"$USERN" "$HOME_TAR" || true
echo "Δημιουργήθηκε: $HOME_TAR"
echo


# --- 4. Δημιουργία /tmp/[USER]-etc ---
echo "Δημιουργία καταλόγου ${ETC_DIR} και αποθήκευση πληροφοριών..."
sudo rm -rf "${ETC_DIR}"
sudo mkdir -p "${ETC_DIR}"

sudo sh -c "df -h > '${ETC_DIR}/df-h.txt'"
sudo sh -c "date +'%Y-%m-%d %H:%M:%S %:z' > '${ETC_DIR}/date.txt'"

sudo cp -p /etc/group "${ETC_DIR}/group" 
sudo cp -p /etc/passwd "${ETC_DIR}/passwd" 
sudo cp -p /etc/shadow "${ETC_DIR}/shadow" || true

sudo chmod 700 "${ETC_DIR}"
sudo chmod 600 "${ETC_DIR}"/* || true
sudo chown -R "$USERN":"$USERN" "${ETC_DIR}"

# --- 5. tar για [USER]-etc ---
echo "Δημιουργία tar ..."
sudo tar -C "${TMP_DIR}" -cf "${ETC_TAR}" "${USERN}-etc"
sudo chown "$USERN":"$USERN" "${ETC_TAR}" || true
echo "Δημιουργήθηκε: ${ETC_TAR}"
echo

# --- 6. Τελικό αρχείο ---
echo "Συσκευασία όλων  σε ένα τελικό tar.gz στο home..."
cd "${TMP_DIR}"
sudo tar -czf "${FINAL_TAR_GZ}" "$(basename "$HOME_TAR")" "$(basename "$ETC_TAR")"
#sudo tar -C "${TMP_DIR}" -czf "${FINAL_TAR_GZ}" "$(basename "$HOME_TAR")" "$(basename "$ETC_TAR")"
sudo chown "$USERN":"$USERN" "${FINAL_TAR_GZ}"
echo "Τελικό αρχείο: ${FINAL_TAR_GZ}"
echo

# --- 7. Τελικό μήνυμα ---
echo "=============================================="
echo "Η διαδικασία ολοκληρώθηκε."
echo "Το αρχείο για ανέβασμα στο eClass βρίσκεται εδώ:"
echo "  ${FINAL_TAR_GZ}"
echo
echo "Ανεβάστε το αρχείο στο eClass όπως ζητά η εκφώνηση."
echo "=============================================="

