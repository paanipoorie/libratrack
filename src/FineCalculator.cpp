#include "FineCalculator.h"
#include "DateUtils.h"
#include "Member.h"
#include "Loan.h"

#include <vector>

double FineCalculator::getDailyRate() const {
    return 0.25;
}

double FineCalculator::calculateFine(const Loan& loan) const {

    int overdue_days = DateUtils::daysBetween(
        loan.getDueDate(),
        loan.getReturnDate()
    );

    if (overdue_days <= GRACE_PERIOD_DAYS)
        return 0.0;

    int chargeable_days = overdue_days - GRACE_PERIOD_DAYS;

    return chargeable_days * getDailyRate();
}

double FineCalculator::getTotalFines(const std::vector<Loan>& loans) const {

    double total = 0.0;

    for (const auto& loan : loans) {
        total += calculateFine(loan);
    }

    return total;
}

double FineCalculator::applyDiscount(double fine,
                                      const Member& member) const {

    if (member.getType() == Member::MemberType::SENIOR) {
        return fine * 0.5;
    }

    return fine;
}

double FineCalculator::getMaxFine(const std::vector<Loan>& loans) const {

    double max_fine = 0.0;

    for (const auto& loan : loans) {
        double fine = calculateFine(loan);
        if (fine > max_fine)
            max_fine = fine;
    }

    return max_fine;
}

bool FineCalculator::hasPendingFines(const std::vector<Loan>& loans) const {

    for (const auto& loan : loans) {
        if (calculateFine(loan) > 0.0)
            return true;
    }

    return false;
}