/*
	This file is part of cpp-ethereum.

	cpp-ethereum is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	cpp-ethereum is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with cpp-ethereum.  If not, see <http://www.gnu.org/licenses/>.
*/
/** @file Transact.h
 * @author Gav Wood <i@gavwood.com>
 * @date 2015
 */

#pragma once

#include <libdevcore/RLP.h>
#include <libethcore/Common.h>
#include <libethereum/Transaction.h>
#include <QDialog>
#include <QMap>
#include <QList>
#include "Context.h"

namespace Ui { class Transact; }
namespace dev { namespace eth { class Client; } }
namespace dev { namespace solidity { class CompilerStack; } }

class Transact: public QDialog
{
	Q_OBJECT

public:
	explicit Transact(Context* _context, QWidget* _parent = 0);
	~Transact();

	void setEnvironment(QList<dev::KeyPair> _myKeys, dev::eth::Client* _eth, NatSpecFace* _natSpecDB);

private slots:
	void on_destination_currentTextChanged(QString);
	void on_value_valueChanged(int) { updateFee(); }
	void on_gas_valueChanged(int) { updateFee(); }
	void on_valueUnits_currentIndexChanged(int) { updateFee(); }
	void on_gasPriceUnits_currentIndexChanged(int) { updateFee(); }
	void on_gasPrice_valueChanged(int) { updateFee(); }
	void on_data_textChanged() { rejigData(); }
	void on_optimize_clicked() { rejigData(); }
	void on_send_clicked();
	void on_debug_clicked();
	void on_cancel_clicked() { close(); }

private:
	dev::eth::Client* ethereum() { return m_ethereum; }
	void rejigData();

	void updateDestination();
	void updateFee();
	bool isCreation() const;
	dev::u256 fee() const;
	dev::u256 total() const;
	dev::u256 value() const;
	dev::u256 gasPrice() const;

	std::string getFunctionHashes(dev::solidity::CompilerStack const& _compiler, std::string const& _contractName = std::string());

	Ui::Transact* ui;

	unsigned m_backupGas;
	dev::bytes m_data;

	QList<dev::KeyPair> m_myKeys;
	dev::eth::Client* m_ethereum;
	Context* m_context;
	NatSpecFace* m_natSpecDB;
};
